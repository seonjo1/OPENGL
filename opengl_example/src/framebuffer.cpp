#include "framebuffer.h"

FramebufferUPtr Framebuffer::Create(const TexturePtr colorAttachment) {
	auto framebuffer = FramebufferUPtr(new Framebuffer());
	if (!framebuffer->InitWithColorAttachment(colorAttachment))
		return nullptr;
	return std::move(framebuffer);
}

Framebuffer::~Framebuffer() {
	if (m_depthStencilBuffer) {
		glDeleteRenderbuffers(1, &m_depthStencilBuffer);
	}
	if (m_framebuffer) {
		glDeleteFramebuffers(1, &m_framebuffer);
	}
}

void Framebuffer::BindToDefault() {
	// 화면에다 그림을 그리는 방법으로 전환
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Framebuffer::Bind() const {
	glBindFramebuffer(GL_FRAMEBUFFER, m_framebuffer);
}

bool Framebuffer::InitWithColorAttachment(const TexturePtr colorAttachment) {
	m_colorAttachment = colorAttachment;

	// framebuffer object 생성 후 bind
	glGenFramebuffers(1, &m_framebuffer);
	glBindFramebuffer(GL_FRAMEBUFFER, m_framebuffer);

	// binding 해놓은 framebuffer에 color buffer를 texture로 붙이는 작업
	// (color buffer는 texture_2D 형태이고 colorAttachment 안에 들어있는
	// 	color object id값을 가져와서 붙이는 작업)
	glFramebufferTexture2D(GL_FRAMEBUFFER,
		GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D,
		colorAttachment->Get(), 0);
	
	// render buffer 생성 후 bind
	glGenRenderbuffers(1, &m_depthStencilBuffer);
	glBindRenderbuffer(GL_RENDERBUFFER, m_depthStencilBuffer);
	
	// render buffer의 크기와 픽셀 포멧(GL_DEPTH24_STENCIL8)을 결정
	glRenderbufferStorage(
		GL_RENDERBUFFER, GL_DEPTH24_STENCIL8,
		colorAttachment->GetWidth(), colorAttachment->GetHeight());

	// 설정 끝났으면 default render buffer로 전환 (bind 함수에서 id자리에 0을 넣으면 default 값이 설정)
	glBindRenderbuffer(GL_RENDERBUFFER, 0);

	// freame buffer에 render buffer 적용 (GL_Depth_Stencil 타입)
	glFramebufferRenderbuffer(
		GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT,
		GL_RENDERBUFFER, m_depthStencilBuffer);

	// frame buffer 상태 체크
	auto result = glCheckFramebufferStatus(GL_FRAMEBUFFER);
	if (result != GL_FRAMEBUFFER_COMPLETE) {
		SPDLOG_ERROR("failed to create framebuffer: {}", result);
		return false;
	}

	BindToDefault();

	return true;
}
