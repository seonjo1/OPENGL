#include "context.h"
#include "image.h"
#include <imgui.h>

ContextUPtr Context::Create()
{
	auto context = ContextUPtr(new Context());
	if (!context->Init())
		return nullptr;
	return std::move(context);
}

void Context::Reshape(int width, int height)
{
	m_width = width;
	m_height = height;
	glViewport(0, 0, m_width, m_height);
}

void Context::ProcessInput(GLFWwindow *window)
{
	if (!m_cameraControl)
		return;
	
	const float cameraSpeed = 0.025f;
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		m_cameraPos += cameraSpeed * m_cameraFront;
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		m_cameraPos -= cameraSpeed * m_cameraFront;

	auto cameraRight = glm::normalize(glm::cross(m_cameraUp, -m_cameraFront));
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		m_cameraPos += cameraSpeed * cameraRight;
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		m_cameraPos -= cameraSpeed * cameraRight;
	
	auto cameraUp = glm::normalize(glm::cross(-m_cameraFront, cameraRight));
	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
		m_cameraPos += cameraSpeed * cameraUp;
	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
		m_cameraPos -= cameraSpeed * cameraUp;
}

void Context::MouseMove(double x, double y)
{
	if (!m_cameraControl)
		return;
	auto pos = glm::vec2((float)x, (float)y);
	auto deltaPos = pos - m_prevMousePos;

	const float cameraRotSpeed = 0.4f;
	m_cameraYaw -= deltaPos.x * cameraRotSpeed;
	m_cameraPitch -= deltaPos.y * cameraRotSpeed;

	if (m_cameraYaw < 0.0f) m_cameraYaw += 360.0f;
	if (m_cameraYaw > 360.0f) m_cameraYaw -= 360.0f;

	if (m_cameraPitch > 89.0f) m_cameraPitch = 89.0f;
	if (m_cameraPitch < -89.0f) m_cameraPitch = -89.0f;

	m_prevMousePos = pos;
}

void Context::MouseButton(int button, int action, double x, double y)
{
	if (button == GLFW_MOUSE_BUTTON_RIGHT)
	{
		if (action == GLFW_PRESS)
		{ // 마우스 조작 시작 시점에 현재 마우스 커서 위치 저장
			m_prevMousePos = glm::vec2((float)x, (float)y);
			m_cameraControl = true;
		}
		else if (action == GLFW_RELEASE)
			m_cameraControl = false;
	}
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
	ShaderPtr vertShader = Shader::CreateFromFile("./shader/lighting.vs", GL_VERTEX_SHADER);
	ShaderPtr fragShader = Shader::CreateFromFile("./shader/lighting.fs", GL_FRAGMENT_SHADER);
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

	return true;
}

void Context::Render() {
	//ImGui::Begin ~ ImGui::End 가 1개의 window가 된다
	if (ImGui::Begin("ui window"))
	{
		if(ImGui::ColorEdit4("clear color", glm::value_ptr(m_clearColor)))
			glClearColor(m_clearColor.x, m_clearColor.y, m_clearColor.z, m_clearColor.w);
		ImGui::Separator();
		ImGui::DragFloat3("camera pos", glm::value_ptr(m_cameraPos), 0.01f);
		ImGui::DragFloat("camera yaw", &m_cameraYaw, 0.5f);
		ImGui::DragFloat("camera pitch", &m_cameraPitch, 0.5f, -89.0f, 89.0f);
		ImGui::Separator();
		if (ImGui::Button("reset camera"))
		{
			m_cameraYaw = 0.0f;
			m_cameraPitch = 0.0f;
			m_cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
		}
	}
	ImGui::End();

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
	
	m_cameraFront =
		glm::rotate(glm::mat4(1.0f), glm::radians(m_cameraYaw), glm::vec3(0.0f, 1.0f, 0.0f)) *
		glm::rotate(glm::mat4(1.0f), glm::radians(m_cameraPitch), glm::vec3(1.0f, 0.0f, 0.0f)) *
		glm::vec4(0.0f, 0.0f, -1.0f, 0.0f); // 마지막 값이 0이면 평행이동 불가

	auto projection = glm::perspective(glm::radians(45.0f), (float)m_width / (float)m_height, 0.01f, 30.0f);
	auto view = glm::lookAt(
		m_cameraPos,
		m_cameraPos + m_cameraFront,
		m_cameraUp
	);

	for (size_t i = 0; i < cubePositions.size(); i++){
		auto& pos = cubePositions[i];
		auto model = glm::translate(glm::mat4(1.0f), pos);
		model = glm::rotate(model, glm::radians((float)glfwGetTime() * 120.0f + 20.0f * (float)i), glm::vec3(1.0f, 0.5f, 0.0f));
		auto transform = projection * view * model;
		m_program->SetUniform("transform", transform);
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	}
}
