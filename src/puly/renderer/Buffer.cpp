#include "Buffer.h"

#include "Renderer.h"
#include "..//lowlevel/debugging/Log.h"

#include "../opengl/OpenGLBuffer.h"

namespace Puly {

	VertexBuffer* VertexBuffer::Create(float* vertices, uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:
			PL_LOG_ERROR("Graphics api not supported!");
			break;
		case RendererAPI::API::OpenGL:
			return new OpenGLVertexBuffer(vertices, size);
			break;
		}
	}

	IndexBuffer* IndexBuffer::Create(uint32_t* indices, uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:
			PL_LOG_ERROR("Graphics api not supported!");
			break;
		case RendererAPI::API::OpenGL:
			return new OpenGLIndexBuffer(indices, size);
			break;
		}
	}

}