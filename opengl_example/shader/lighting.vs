#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoord;

uniform mat4 transform;
uniform mat4 modelTransform;

out vec3 normal;
out vec2 texCoord;
out vec3 position;

void main()
{
	gl_Position = transform * vec4(aPos, 1.0);
	normal = (transpose(inverse(modelTransform)) * vec4(aNormal, 0.0)).xyz; // world coordinate 상에서의 법선 벡터
	// position과 다르게 normal은 점이 아닌 벡터이므로 inverse transpose를 통해 변환을 해야 제대로 변환된 값이 나옴
	texCoord = aTexCoord;
	position = (modelTransform * vec4(aPos, 1.0)).xyz; // world coordinate 상에서의 위치
}
