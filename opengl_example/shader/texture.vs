#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexCoord; //텍스처 좌표

uniform mat4 transform; // 초기화 안하면 0으로 이루어진 matrix임

out vec4 vertexColor;
out vec2 texCoord;

void main()
{
	gl_Position = transform * vec4(aPos, 1.0); 
	vertexColor = vec4(aColor, 1.0);
	texCoord = aTexCoord;
}