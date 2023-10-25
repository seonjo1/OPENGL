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
	// 점의 위치 x, y, z
	float vertices[] = {
		0.5f, 0.5f, 0.0f,   // top right
		0.5f, -0.5f, 0.0f,  // bottom right
		-0.5f, -0.5f, 0.0f, // bottom left
		-0.5f, 0.5f, 0.0f   // top left
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
	glGenVertexArrays(1, &m_vertexArrayObject); // array 생성
	glBindVertexArray(m_vertexArrayObject); // array binding

	// 2. VBO 생성 후 binding 하고 데이터 복사
	glGenBuffers(1, &m_vertexBuffer); // vertexBuffer 생성 (vertexBuffer : 각 vertex의 위치, 색상 등이 들어가는 버퍼)
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer); // GL_ARRAY_BUFFER와 vertexBuffer를 binding (GL_ARRAY_BUFFER : VBO (vertex buffer object))
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 12, vertices, GL_STATIC_DRAW); // buffer에 데이터를 복사 한다.

	// 3. vertex attribute 설정 (VBO를 읽기 위한 정보 저장)
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, 0);

	// 4. EBO 생성 후 binding 하고 데이터 복사 (어처피 정수가 들어오므로 attribute array 설정은 필요 없음)
	glGenBuffers(1, &m_indexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint32_t) * 6, indices, GL_STATIC_DRAW);

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
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}
