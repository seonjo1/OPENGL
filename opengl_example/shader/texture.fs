#version 330 core
in vec4 vertexColor;
in vec2 texCoord; 
out vec4 fragColor;

//Sampler는 텍스처 객체에 대한 데이터타입이다.
uniform sampler2D tex;

void main()
{
	//texture 함수에 sampler와 texCoord의 텍스처 좌표를 입력하면 설정해 놓은
	//텍스처 파라미터를 사용하여 컬러 값을 샘플링한다.
	vec4 pixel = texture(tex, texCoord);
	if (pixel.a < 0.01)
		discard; // 업데이트 x로 depth 기록 x
	fragColor = pixel;
}