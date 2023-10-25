#include "context.h"

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
	// 삼각형 3개 점의 위치 x, y, z
	float vertices[] = {
		-0.5f, -0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		0.0f, 0.5f, 0.0f
	};	
	// 순서 주의
	// 1. VAO 생성 후 binding
	glGenVertexArrays(1, &m_vertexArrayObject); // array 생성
	glBindVertexArray(m_vertexArrayObject); // array binding

	// 2. VBO 생성 후 binding
	glGenBuffers(1, &m_vertexBuffer); // vertexBuffer 생성 (vertexBuffer : 각 vertex의 위치, 색상 등이 들어가는 버퍼)
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer); // GL_ARRAY_BUFFER와 vertexBuffer를 binding (GL_ARRAY_BUFFER : VBO (vertex buffer object))
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 9, vertices, GL_STATIC_DRAW); // buffer에 데이터를 복사 한다.

	// 3. vertex attribute 설정 (VBO를 읽기 위한 정보 저장)
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, 0);

	// Vertex Shader와 Fragment Shader 생성
	// program class에 shared pointer로 넣어줘야 하므로 shaderPtr로 형변환해서 받음
	ShaderPtr vertShader = Shader::CreateFromFile("./shader/simple.vs", GL_VERTEX_SHADER);
	ShaderPtr fragShader = Shader::CreateFromFile("./shader/simple.fs", GL_FRAGMENT_SHADER);

	if (!vertShader || !fragShader)
		return false;
	SPDLOG_INFO("vertex shader id: {}", vertShader->Get());
	SPDLOG_INFO("fragment shader id: {}", fragShader->Get());

	// program 생성
	m_program = Program::Create({fragShader, vertShader}); // {a, b} 벡터를 인자로 넣어줌
	if (!m_program)
		return false;
	SPDLOG_INFO("program id: {}", m_program->Get());

	glClearColor(0.1f, 0.2f, 0.3f, 0.0f);

	return true;
}

void Context::Render()
{
	glClear(GL_COLOR_BUFFER_BIT);

	glUseProgram(m_program->Get());
	glDrawArrays(GL_TRIANGLES, 0, 3);
}