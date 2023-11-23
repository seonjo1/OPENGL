#version 330 core
in vec4 vertexColor;
in vec2 texCoord;
out vec4 fragColor;

uniform sampler2D tex;
uniform float gamma;

// 밝기 조절 fragment shader
void main()
{
	vec4 pixel = texture(tex, texCoord);
	// gamma 만큼 제곱
	// rgb는 항상 0 ~ 1 의 값이므로
	// gamma가 1보다 커지면 rgb값이 작아진다 (어두워짐)
	// gamma가 1보다 작아지면 rgb값이 커진다 (밝아짐)
	fragColor = vec4(pow(pixel.rgb, vec3(gamma)), 1.0);
}
