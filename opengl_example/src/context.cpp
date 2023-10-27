#include "context.h"
#include "image.h"

ContextUPtr Context::Create()
{
	auto context = ContextUPtr(new Context());
	if (!context->Init())
		return nullptr;
	return std::move(context);
}

// context 초기화 함수
bool Context::Init()
{
	// 점의 위치 x, y, z
	float vertices[] = {
		0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,  // top right, red
		0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, // bottom right, green
		-0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, // bottom left, blue
		-0.5f, 0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f // top left, yellow
	};
	
	// 중복되는 점의 x, y, z입력을 피하기 위해
	// Element Buffer Object (EBO)를 사용   << index buffer라고도 불림
	// vertices에 있는 점들을 index로 표현한 버전
	uint32_t indices[] = {
		0, 1, 3, // first triangle
		1, 2, 3, // second triangle
	};

	// 순서 주의
	// 1. VAO 생성 후 binding
	m_vertexLayout = VertexLayout::Create();

	// 2. VBO 생성 후 binding 하고 데이터 복사
	m_vertexBuffer = Buffer::CreateWithData(GL_ARRAY_BUFFER, GL_STATIC_DRAW, vertices, sizeof(float) * 32);

	// 3. VAO 의 attribute 설정 (VBO를 읽기 위한 정보 저장)
	m_vertexLayout->SetAttrib(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, 0);
	m_vertexLayout->SetAttrib(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, sizeof(float) * 3);
	m_vertexLayout->SetAttrib(2, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 8, sizeof(float) * 6);

	// 4. EBO 생성 후 binding 하고 데이터 복사 (어처피 정수가 들어오므로 attribute array 설정은 필요 없음)
	m_indexBuffer = Buffer::CreateWithData(GL_ELEMENT_ARRAY_BUFFER, GL_STATIC_DRAW, indices, sizeof(uint32_t) * 6);

	// Vertex Shader와 Fragment Shader 생성
	// program class에 shared pointer로 넣어줘야 하므로 shaderPtr로 형변환해서 받음
	ShaderPtr vertShader = Shader::CreateFromFile("./shader/texture.vs", GL_VERTEX_SHADER);
	ShaderPtr fragShader = Shader::CreateFromFile("./shader/texture.fs", GL_FRAGMENT_SHADER);

	if (!vertShader || !fragShader)
		return false;
	SPDLOG_INFO("vertex shader id: {}", vertShader->Get());
	SPDLOG_INFO("fragment shader id: {}", fragShader->Get());

	// program 생성
	m_program = Program::Create({fragShader, vertShader}); // {a, b} 벡터를 인자로 넣어줌
	if (!m_program)
		return false;
	SPDLOG_INFO("program id: {}", m_program->Get());

	// // uniform 함수값 설정
	// auto loc = glGetUniformLocation(m_program->Get(), "Color");
	// m_program->Use();
	// glUniform4f(loc, 0.0f, 1.0f, 0.0f, 1.0f);
	// //

	glClearColor(0.1f, 0.2f, 0.3f, 0.0f);

	// 이미지 생성
	auto image = Image::Load("./image/container.jpg");
	if (!image)
		return false;
	SPDLOG_INFO("image: {}x{}, {} channels", image->GetWidth(), image->GetHeight(), image->GetChannelCount());

	glGenTextures(1, &m_texture); // 텍스처 생성
	glBindTexture(GL_TEXTURE_2D, m_texture); // 텍스처 바인딩
	// 텍스처 설정
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	//텍스처 GPU에 복사
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image->GetWidth(), image->GetHeight(), 0, GL_RGB, GL_UNSIGNED_BYTE, image->GetData());

	return true;
}

void Context::Render()
{
	glClear(GL_COLOR_BUFFER_BIT);

	m_program->Use();
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}
