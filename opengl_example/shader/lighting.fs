#version 330 core
in vec3 normal;
in vec2 texCoord;
out vec4 fragColor;

uniform vec3 lightColor; // 광원의 색
uniform vec3 objectColor; // 물체의 색
uniform float ambientStrength; // 전체 밝기의 크기를 0 ~ 1의 값으로 표현 (기본 밝기라고 생각)

void main()
{
	vec3 ambient = ambientStrength * lightColor; // 벡터들의 곱은 각 x, y, z끼리의 곱으로 계산된다.
	vec3 result = ambient * objectColor;
	fragColor = vec4(result, 1.0);
}