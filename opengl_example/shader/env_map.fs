#version 330 core

out vec4 fragColor;

in vec3 normal;
in vec3 position;

uniform vec3 cameraPos;
uniform samplerCube skybox;

void main()
{
	// 시선 벡터
	vec3 I = normalize(position - cameraPos);
	// 반사 벡터
	vec3 R = reflect(I, normalize(normal));
	// 반사 벡터에 부딪히는 부분의 rgb를 그린다.
	fragColor = vec4(texture(skybox, R).rgb, 1.0);
}