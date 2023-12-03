#version 330 core
in vec3 normal;
in vec2 texCoord;
in vec3 position;
out vec4 fragColor;

uniform vec3 viewPos;
uniform int blinn;

struct Light
{
	vec3 position;
	vec3 direction; // 방향
	vec2 cutoff; // 각도
	vec3 attenuation;
	vec3 ambient;  // 광원의 ambient strength
	vec3 diffuse;  // 광원의 분산광
	vec3 specular; // 광원의 반사광
};
uniform Light light;

struct Material
{
	sampler2D diffuse; //ambient와 diffuse를 통일
	sampler2D specular;
	float shininess; // 표면이 얼마나 반짝거리느냐
};
uniform Material material;

void main()
{
	vec3 texColor = texture(material.diffuse, texCoord).xyz;
	vec3 ambient = texColor * light.ambient; // 벡터들의 곱은 각 x, y, z끼리의 곱으로 계산된다.

	float dist = length(light.position - position);
	vec3 distPoly = vec3(1.0, dist, dist * dist); // 1.0, d, d^2
	float attenuation = 1.0 / dot(distPoly, light.attenuation);
	// attenuation =  1 / (1.0 * Kc + d * Kl + d^2 * Kq) << 감쇠 값
	vec3 lightDir = normalize(light.position - position); // - 빛의 방향 벡터

	 // 광원과 물체 사이의 벡터와 빛의 방향 벡터 사의의 각도의 코사인값
	float theta = dot(lightDir, normalize(-light.direction));
	vec3 result = ambient;
	float intensity = clamp((theta - light.cutoff[1]) / (light.cutoff[0] - light.cutoff[1]), 0.0, 1.0);
	// cutoff[0] = 경계값
	// cutoff[1] = offset ( offset 까지는 빛이 약해지면서 존재 )
	// 이 둘을 이용해서 cutoff[0] ~ cutoff[1]의 값은 선형보간
	if (intensity > 0.0)
	{
		vec3 pixelNorm = normalize(normal); // 물체표면에 대한 법선벡터
		float diff = max(dot(pixelNorm, lightDir), 0.0);
		vec3 diffuse = diff * texColor * light.diffuse;

		vec3 specColor = texture2D(material.specular, texCoord).xyz;
		float spec = 0.0;
		if (blinn == 0)
		{
			// 기존 spec 계산방법 (phong shading)
			vec3 viewDir = normalize(viewPos - position);
			vec3 reflectDir = reflect(-lightDir, pixelNorm);
			spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
		}
		else
		{
			// blinn shading
			vec3 viewDir = normalize(viewPos - position);
			vec3 halfDir = normalize(lightDir + viewDir);
			spec = pow(max(dot(halfDir, pixelNorm), 0.0), material.shininess);
		}
		vec3 specular = spec * specColor * light.specular;
		result += (diffuse + specular) * intensity;
	}

	result *= attenuation;  // 감쇠

	fragColor = vec4(result, 1.0);
	
	// depth visualization
	// fragColor = vec4(vec3(gl_FragCoord.z), 1.0);
	// {gl_FragCoord.z , gl_FragCoord.z, gl_FragCoord.z, 1}
}