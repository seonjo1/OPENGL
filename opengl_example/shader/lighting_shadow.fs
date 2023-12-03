#version 330 core

out vec4 fragColor;

in VS_OUT {
	vec3 fragPos;
	vec3 normal;
	vec2 texCoord;
	vec4 fragPosLight;
} fs_in;

uniform vec3 viewPos;
struct Light {
	int directional;
	vec3 position;
	vec3 direction;
	vec2 cutoff;
	vec3 attenuation;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};
uniform Light light;

struct Material {
	sampler2D diffuse;
	sampler2D specular;
	float shininess;
};
uniform Material material;
uniform int blinn;
uniform sampler2D shadowMap;

float ShadowCalculation(vec4 fragPosLight, vec3 normal, vec3 lightDir) {
	// -1 ~ 1 범위의 값
	vec3 projCoords = fragPosLight.xyz / fragPosLight.w;
	// 0 ~ 1 범위의 값으로 normalizing
	projCoords = projCoords * 0.5 + 0.5;
	// get closest depth(빛의 입장에서 가장 가까이 있는 물체 기준 depth)
	float closestDepth = texture(shadowMap, projCoords.xy).r;
	// 현재 좌표의 depth값
	float currentDepth = projCoords.z;
	// light direction과 surface normal 간의 각도에 따라 bias를 바꾼다. ( 0.001 <= bias <= 0.02)
	float bias = max(0.02 * (1.0 - dot(normal, lightDir)), 0.001);
	// PCF 현재 픽셀 주변의 9개의 픽셀의 그림자 유무를 판단하여 그림자의 색을 조절
	float shadow = 0.0;
	vec2 texelSize = 1.0 / textureSize(shadowMap, 0);
	for(int x = -1; x <= 1; ++x) {
		for (int y = -1; y <= 1; ++y) {
			float pcfDepth = texture(shadowMap,
				projCoords.xy + vec2(x, y) * texelSize).r;
			shadow += currentDepth - bias > pcfDepth ? 1.0 : 0.0;
		}
	}
	shadow /= 9.0;
	return shadow;
}

void main() {
	vec3 texColor = texture2D(material.diffuse, fs_in.texCoord).xyz;
	vec3 ambient = texColor * light.ambient;

	vec3 result = ambient;
	vec3 lightDir;
	float intensity = 1.0;
	float attenuation = 1.0;
	if (light.directional == 1) {
	lightDir = normalize(-light.direction);
	}
	else {
	float dist = length(light.position - fs_in.fragPos);
	vec3 distPoly = vec3(1.0, dist, dist*dist);
	attenuation = 1.0 / dot(distPoly, light.attenuation);
	lightDir = (light.position - fs_in.fragPos) / dist;
	
	float theta = dot(lightDir, normalize(-light.direction));
	intensity = clamp(
		(theta - light.cutoff[1]) / (light.cutoff[0] - light.cutoff[1]),
		0.0, 1.0);
	}

	if (intensity > 0.0) {
	vec3 pixelNorm = normalize(fs_in.normal);
	float diff = max(dot(pixelNorm, lightDir), 0.0);
	vec3 diffuse = diff * texColor * light.diffuse;

	vec3 specColor = texture2D(material.specular, fs_in.texCoord).xyz;
	float spec = 0.0;
	if (blinn == 0) {
		vec3 viewDir = normalize(viewPos - fs_in.fragPos);
		vec3 reflectDir = reflect(-lightDir, pixelNorm);
		spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
	}
	else {
		vec3 viewDir = normalize(viewPos - fs_in.fragPos);
		vec3 halfDir = normalize(lightDir + viewDir);
		spec = pow(max(dot(halfDir, pixelNorm), 0.0), material.shininess);
	}
	vec3 specular = spec * specColor * light.specular;
	// 추가된 부분 shadow가 0이면 색칠 1이면 그림자
	float shadow = ShadowCalculation(fs_in.fragPosLight, pixelNorm, lightDir);

	result += (diffuse + specular) * intensity * (1.0 - shadow);
	}

	result *= attenuation;
	fragColor = vec4(result, 1.0);
}