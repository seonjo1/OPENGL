#ifndef __CONTEXT_H__
#define __CONTEXT_H__

#include "common.h"
#include "shader.h"
#include "program.h"
#include "buffer.h"
#include "vertex_layout.h"
#include "texture.h"
#include "mesh.h"
#include "model.h"

// main의 내용에서 그림을 그리는 렌더링 부분을 분리시키는 클래스
CLASS_PTR(Context)
class Context
{
public:
	static ContextUPtr Create();
	void Render();
	void ProcessInput(GLFWwindow *window);
	void Reshape(int width, int height);
	void MouseMove(double x, double y);
	void MouseButton(int button, int action, double x, double y);

private:
	Context() {}
	bool Init();
	ProgramUPtr m_program;
	ProgramUPtr m_simpleProgram;
	ProgramUPtr m_textureProgram;

	MeshUPtr m_box;
	MeshUPtr m_plane;

	// animation
	bool m_animation { true };

	//clear color
	glm::vec4 m_clearColor { glm::vec4(0.1f, 0.2f, 0.3f, 0.0f) };

	//light parameter
	struct Light
	{
		glm::vec3 position { glm::vec3(1.0f, 4.0f, 4.0f) };
		glm::vec3 direction {glm::vec3(-1.0f, -1.0f, -1.0f)};
		glm::vec2 cutoff { glm::vec2(120.0f, 5.0f) }; // { inner cut-off angle, offset angle }
		float distance { 128.0f };
		glm::vec3 ambient { glm::vec3(0.1f, 0.1f, 0.1f) };
		glm::vec3 diffuse { glm::vec3(0.8f, 0.8f, 0.8f) };
		glm::vec3 specular { glm::vec3(1.0f, 1.0f, 1.0f) };
	};
	Light m_light;
	
	//손전등 모드
	bool m_flashLightMode { false };

	MaterialPtr m_planeMaterial;
	MaterialPtr m_box1Material;
	MaterialPtr m_box2Material;
	TexturePtr m_windowTexture;

	// camera parameter
	bool m_cameraControl { false };
	glm::vec2 m_prevMousePos { glm::vec2(0.0f)};
	float m_cameraPitch { -20.0f };
	float m_cameraYaw { 0.0f };
	// 카메라가 바라보는 방향
	glm::vec3 m_cameraFront { glm::vec3(0.0f, -1.0f, 0.0f) };
	// 카메라의 위치
	glm::vec3 m_cameraPos { glm::vec3(0.0f, 2.5f, 8.0f) };
	// 카메라의 수직 방향
	glm::vec3 m_cameraUp { glm::vec3(0.0f, 1.0f, 0.0f) };

	int m_width {WINDOW_WIDTH};
	int m_height {WINDOW_HEIGHT};
};

#endif