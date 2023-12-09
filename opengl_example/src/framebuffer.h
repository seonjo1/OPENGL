#ifndef __FRAMEBUFFER_H__
#define __FRAMEBUFFER_H__

#include "texture.h"

CLASS_PTR(Framebuffer);
class Framebuffer
{
	public:
		// 1개의 framebuffer에 colorAttachment가 여러개 있을 수 있음
		static FramebufferUPtr Create(const std::vector<TexturePtr> &colorAttachments);
		static void BindToDefault();
		~Framebuffer();

		const uint32_t Get() const { return m_framebuffer; }
		void Bind() const;
		int GetColorAttachmentCount() const { return (int)m_colorAttachments.size(); }
		const TexturePtr GetColorAttachment(int index = 0) const { return m_colorAttachments[index]; }

	private:
		Framebuffer() {}
		bool InitWithColorAttachments(const std::vector<TexturePtr> &colorAttachments);

		uint32_t m_framebuffer { 0 };
		uint32_t m_depthStencilBuffer { 0 };
		std::vector<TexturePtr> m_colorAttachments;
};

#endif