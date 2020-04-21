#include "VertexArray.h"
#include "Renderer.h"

#include "../opengl/OpenGLVertexArray.h"

namespace Puly {
	VertexArray* VertexArray::Create()
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:
			PL_LOG_ERROR("Graphics api not supported!");
			break;
		case RendererAPI::API::OpenGL:
			return new OpenGLVertexArray();
			break;
		}

		return nullptr;
	}
}
