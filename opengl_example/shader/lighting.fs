#version 330 core
in vec3 normal;
in vec2 texCoord;
in vec3 position;
out vec4 fragColor;

uniform vec3 viewPos;

struct Light
{
	vec3 direction;
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
	vec3 texColor = texture2D(material.diffuse, texCoord).xyz;
	vec3 ambient = texColor * light.ambient; // 벡터들의 곱은 각 x, y, z끼리의 곱으로 계산된다.

	vec3 lightDir = normalize(-light.direction); // - 빛의 방향 벡터
	vec3 pixelNorm = normalize(normal);
	// normal을 다시 normalize 하는 이유
	// - vertex shader에서 계산된 normal은 rasterization되는 과정에서 선형보간이 진행됨
	// - unit vector간의 선형 보간 결과는 unit vector 보장을 못하기 때문에 normalization 해야함
	float diff = max(dot(pixelNorm, lightDir), 0.0);
	vec3 diffuse = diff * texColor * light.diffuse; // max를 이용하여 음수일때는 diffuse = 0

	vec3 specColor = texture2D(material.specular, texCoord).xyz;
	vec3 viewDir = normalize(viewPos - position);
	vec3 reflectDir = reflect(-lightDir, pixelNorm); // reflect : 반사광의 방향벡터를 구하는 함수
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess); // specular의 면적 조절
	// pow를 사용하면 specularShininess가 1보다 크면 반사광의 영역이(원이) 커지고, 1보다 작으면 반사광의 영역이(원이) 작아진다.
	vec3 specular = spec * specColor * light.specular; // specular의 빛의 정도를 조절

	vec3 result = ambient + diffuse + specular;

	fragColor = vec4(result, 1.0);
}