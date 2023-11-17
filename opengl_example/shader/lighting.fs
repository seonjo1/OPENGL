#version 330 core
in vec3 normal;
in vec2 texCoord;
in vec3 position;
out vec4 fragColor;

uniform vec3 viewPos;

struct Light
{
	vec3 position;
	vec3 direction; // 방향
	float cutoff; // 각도
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
	vec3 lightDir = normalize(light.position - position) / dist; // - 빛의 방향 벡터

	float theta = dot(lightDir, normalize(-light.direction));
	 // 광원과 물체 사이의 벡터와 빛의 방향 벡터 사의의 각도의 코사인값
	vec3 result = ambient;

	if (theta > light.cutoff) // 우리가 지정한 cos 값인 light.cutoff 보다 theta가 클경우 각도의 범위를 넘어간 것이므로 빛 x
	{
		vec3 pixelNorm = normalize(normal); // 물체표면에 대한 법선벡터
		float diff = max(dot(pixelNorm, lightDir), 0.0);
		vec3 diffuse = diff * texColor * light.diffuse;

		vec3 specColor = texture2D(material.specular, texCoord).xyz;
		vec3 viewDir = normalize(viewPos - position);
		vec3 reflectDir = reflect(-lightDir, pixelNorm);  // 반사광의 벡터
		float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
		vec3 specular = spec * specColor * light.specular;

		result += diffuse + specular;
	}

	result *= attenuation;  // 감쇠

	fragColor = vec4(result, 1.0);
}