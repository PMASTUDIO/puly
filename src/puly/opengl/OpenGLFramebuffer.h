#pragma once

#include "../renderer/Framebuffer.h"

namespace Puly {
	class OpenGLFrameBuffer : public Framebuffer {
	public:
		OpenGLFrameBuffer(const FramebufferSpecification& spec);
		virtual ~OpenGLFrameBuffer();

		void Resize();

		virtual void Bind() override;
		virtual void Unbind() override;

		virtual const FramebufferSpecification& GetSpecification() const override { return m_Specs; }
		virtual FramebufferSpecification& GetSpecification() override { return m_Specs; }


		virtual uint32_t GetColorAttachmentRendererId() const override { return m_ColorAttachment; }

	private:
		uint32_t m_RendererID;
		uint32_t m_ColorAttachment, m_DepthAttachment;
		FramebufferSpecification m_Specs;
	};
}