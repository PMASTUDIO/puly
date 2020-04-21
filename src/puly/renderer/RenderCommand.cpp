#include "RenderCommand.h"

#include "..//opengl/OpenGLRendererApi.h"

namespace Puly {

	RendererAPI* RenderCommand::s_RendererAPI = new OpengGLRendererAPI;

}