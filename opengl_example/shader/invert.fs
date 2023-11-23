#version 330 core
in vec4 vertexColor;
in vec2 texCoord;
out vec4 fragColor;

uniform sampler2D tex;

// 색 반전 fragment shader
void main()
{
	vec4 pixel = texture(tex, texCoord);
	fragColor = vec4(1.0 - pixel.rgb, 1.0);
}