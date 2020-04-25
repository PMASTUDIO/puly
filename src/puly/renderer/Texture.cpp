#include "Texture.h"

#include <memory>

#include "..//opengl/OpenGlTexture2D.h"

namespace Puly {
	std::shared_ptr<Texture> Texture2D::Create(std::string path)
	{
		return std::make_shared<OpenGLTexture2D>(path);
	}
}

