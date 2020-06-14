#pragma once

#include <memory>
#include <stdint.h>

namespace Puly {

	struct FramebufferSpecification {
		uint32_t Width, Height;
		uint32_t Samples = 1;
		bool SwapChainTarget = false;
	};

	class Framebuffer {
	public:
		virtual void Bind() = 0;
		virtual void Unbind() = 0;

		virtual uint32_t GetColorAttachmentRendererId() const = 0;

		virtual const FramebufferSpecification& GetSpecification() const = 0;
		virtual FramebufferSpecification& GetSpecification() = 0;

		static std::shared_ptr<Framebuffer> Create(const FramebufferSpecification& specs);
	};
}