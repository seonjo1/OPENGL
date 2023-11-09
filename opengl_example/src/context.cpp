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
	float vertices[] = {
	-0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
	0.5f, -0.5f, -0.5f, 1.0f, 0.0f,
	0.5f,  0.5f, -0.5f, 1.0f, 1.0f,
	-0.5f,  0.5f, -0.5f, 0.0f, 1.0f,

	-0.5f, -0.5f,  0.5f, 0.0f, 0.0f,
	0.5f, -0.5f,  0.5f, 1.0f, 0.0f,
	0.5f,  0.5f,  0.5f, 1.0f, 1.0f,
	-0.5f,  0.5f,  0.5f, 0.0f, 1.0f,

	-0.5f,  0.5f,  0.5f, 1.0f, 0.0f,
	-0.5f,  0.5f, -0.5f, 1.0f, 1.0f,
	-0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f, 0.0f, 0.0f,

	0.5f,  0.5f,  0.5f, 1.0f, 0.0f,
	0.5f,  0.5f, -0.5f, 1.0f, 1.0f,
	0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
	0.5f, -0.5f,  0.5f, 0.0f, 0.0f,

	-0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
	0.5f, -0.5f, -0.5f, 1.0f, 1.0f,
	0.5f, -0.5f,  0.5f, 1.0f, 0.0f,
	-0.5f, -0.5f,  0.5f, 0.0f, 0.0f,

	-0.5f,  0.5f, -0.5f, 0.0f, 1.0f,
	0.5f,  0.5f, -0.5f, 1.0f, 1.0f,
	0.5f,  0.5f,  0.5f, 1.0f, 0.0f,
	-0.5f,  0.5f,  0.5f, 0.0f, 0.0f,
	};

	uint32_t indices[] = {
	0,  2,  1,  2,  0,  3,
	4,  5,  6,  6,  7,  4,
	8,  9, 10, 10, 11,  8,
	12, 14, 13, 14, 12, 15,
	16, 17, 18, 18, 19, 16,
	20, 22, 21, 22, 20, 23,
	};

	// 순서 주의
	// 1. VAO 생성 후 binding
	m_vertexLayout = VertexLayout::Create();

	// 2. VBO 생성 후 binding 하고 데이터 복사
	m_vertexBuffer = Buffer::CreateWithData(GL_ARRAY_BUFFER, GL_STATIC_DRAW, vertices, sizeof(float) * 120);

	// 3. VAO 의 attribute 설정 (VBO를 읽기 위한 정보 저장)
	m_vertexLayout->SetAttrib(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 5, 0);
	m_vertexLayout->SetAttrib(2, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 5, sizeof(float) * 3);

	// 4. EBO 생성 후 binding 하고 데이터 복사 (어처피 정수가 들어오므로 attribute array 설정은 필요 없음)
	m_indexBuffer = Buffer::CreateWithData(GL_ELEMENT_ARRAY_BUFFER, GL_STATIC_DRAW, indices, sizeof(uint32_t) * 36);

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

	glClearColor(0.1f, 0.2f, 0.3f, 0.0f);

	// 이미지 생성
	auto image = Image::Load("./image/container.jpg");
	if (!image)
		return false;
	SPDLOG_INFO("image: {}x{}, {} channels", image->GetWidth(), image->GetHeight(), image->GetChannelCount());
	// 텍스처 생성
	m_texture = Texture::CreateFromImage(image.get());
	// UPtr에서 .get()을 사용하면 그냥 포인터를 얻을 수 있음
	
	// 2번째 이미지 생성
	auto image2 = Image::Load("./image/awesomeface.png");
	if (!image2)
		return false;
	SPDLOG_INFO("image2: {}x{}, {} channels", image2->GetWidth(), image2->GetHeight(), image2->GetChannelCount());
	m_texture2 = Texture::CreateFromImage(image2.get());
	
	// 텍스처 0번 슬롯 설정
	// 내가 사용하고자 하는 텍스트 슬롯 번호 지정
	glActiveTexture(GL_TEXTURE0);
	// 해당 슬롯에 원하는 텍스처 id를 이용한 binding
	glBindTexture(GL_TEXTURE_2D, m_texture->Get());

	// 텍스처 1번 슬롯 설정
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, m_texture2->Get());

	m_program->Use();
	m_program->SetUniform("tex", 0);
	m_program->SetUniform("tex2", 1);

	// // x축으로 -55도 회전
	// auto model = glm::rotate(glm::mat4(1.0f), glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	// // 카메라는 원점으로부터 z축 방향으로 -3만큼 떨어짐
	// auto view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -3.0f));
	// // 종횡비 4:3, 세로화각 45도의 원근 투영
	// auto projection = glm::perspective(glm::radians(45.0f), (float)640 / (float)480, 0.01f, 10.0f);
	// auto transform = projection * view * model;
	// m_program->SetUniform("transform", transform);

	return true;
}

void Context::Render() {
	std::vector<glm::vec3> cubePositions = {
		glm::vec3( 0.0f, 0.0f, 0.0f),
		glm::vec3( 2.0f, 5.0f, -15.0f),
		glm::vec3(-1.5f, -2.2f, -2.5f),
		glm::vec3(-3.8f, -2.0f, -12.3f),
		glm::vec3( 2.4f, -0.4f, -3.5f),
		glm::vec3(-1.7f, 3.0f, -7.5f),
		glm::vec3( 1.3f, -2.0f, -2.5f),
		glm::vec3( 1.5f, 2.0f, -2.5f),
		glm::vec3( 1.5f, 0.2f, -1.5f),
		glm::vec3(-1.3f, 1.0f, -1.5f),
	};

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	
	auto projection = glm::perspective(glm::radians(45.0f), (float)WINDOW_WIDTH / (float)WINDOW_HEIGHT, 0.01f, 20.0f);
	auto view = glm::translate(glm::mat4(1.0f),	glm::vec3(0.0f, 0.0f, -3.0f));

	for (size_t i = 0; i < cubePositions.size(); i++){
		auto& pos = cubePositions[i];
		auto model = glm::translate(glm::mat4(1.0f), pos);
		model = glm::rotate(model, glm::radians((float)glfwGetTime() * 120.0f + 20.0f * (float)i), glm::vec3(1.0f, 0.5f, 0.0f));
		auto transform = projection * view * model;
		m_program->SetUniform("transform", transform);
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	}
}
