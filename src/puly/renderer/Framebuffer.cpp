#include "Framebuffer.h"

#include "../opengl/OpenGLFramebuffer.h"

#include "Renderer.h"

namespace Puly {

	std::shared_ptr<Puly::Framebuffer> Puly::Framebuffer::Create(const FramebufferSpecification& specs)
	{
		/*switch (Renderer::GetAPI()){

		case RendererAPI::API::None:
			PL_LOG_ERROR("Rendering api not supported!");
			return nullptr;
		case RendererAPI::API::OpenGL:
			return std::make_shared<OpenGLFrameBuffer>(specs);
		}*/

		std::shared_ptr<Puly::Framebuffer> result;

		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:
			PL_LOG_ERROR("Graphics api not supported!");
			break;
		case RendererAPI::API::OpenGL:
			result = std::make_shared<OpenGLFrameBuffer>(specs);
			return result;
			break;
		}

		PL_LOG_ERROR("Rendering api not supported (IS ERROR)!");
		return nullptr;
	}

}
