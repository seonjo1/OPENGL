#version 330 core
in vec4 vertexColor;
in vec2 texCoord; 
out vec4 fragColor;

//Sampler는 텍스처 객체에 대한 데이터타입이다.
uniform sampler2D tex;
uniform sampler2D tex2;

void main()
{
	fragColor = texture(tex, texCoord) * 0.8 + texture(tex2, texCoord) * 0.2;
	//texture 함수에 sampler와 텍스처 좌표를 입력하면 설정해 놓은
	//텍스처 파라미터를 사용하여 컬러 값을 샘플링한다.
}