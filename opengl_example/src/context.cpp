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

	uint32_t vao = 0;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	return true;
}

void Context::Render()
{
	glClear(GL_COLOR_BUFFER_BIT);

	glUseProgram(m_program->Get());
	glDrawArrays(GL_POINTS, 0, 1);
}