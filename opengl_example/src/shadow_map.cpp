#include "shadow_map.h"

ShadowMapUPtr ShadowMap::Create(int width, int height) {
	auto shadowMap = ShadowMapUPtr(new ShadowMap());
	if (!shadowMap->Init(width, height))
		return nullptr;
	return std::move(shadowMap);
}

ShadowMap::~ShadowMap() {
	if (m_framebuffer) {
		glDeleteFramebuffers(1, &m_framebuffer);
	}
}

void ShadowMap::Bind() const {
	glBindFramebuffer(GL_FRAMEBUFFER, m_framebuffer);
}

bool ShadowMap::Init(int width, int height) {
	// framebuffer.cpp와 비슷한 코드 but color 대신 depth 사용
	glGenFramebuffers(1, &m_framebuffer);
	Bind();

	// depth buffer가 0 ~ 1 사이의 float 값을 가지므로 type에 GL_FLOAT을 넣어줌
	m_shadowMap = Texture::Create(width, height, GL_DEPTH_COMPONENT, GL_FLOAT);
	m_shadowMap->SetFilter(GL_NEAREST, GL_NEAREST);
	m_shadowMap->SetWrap(GL_REPEAT, GL_REPEAT);

	// depth_attachment만 붙이고 color는 신경 안씀
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT,
		GL_TEXTURE_2D, m_shadowMap->Get(), 0);
	// color attachment를 설정 안 했기 때문에 glCheckFramebufferStatus에서 오류가뜸
	// 오류를 막기 위해 Drawbuffer와 ReadBuffer에 GL_NONE을 넣어서 값이 없다는 것을 명시해야 함
	glDrawBuffer(GL_NONE);
	glReadBuffer(GL_NONE);
	auto status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
	if (status != GL_FRAMEBUFFER_COMPLETE) {
		SPDLOG_ERROR("failed to complete shadow map framebuffer: {:x}", status);
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		return false;
	}
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	return true;
}
