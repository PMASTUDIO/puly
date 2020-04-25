#pragma once

#include <GL/glew.h>

#include "..//renderer/Texture.h"

namespace Puly {

	class OpenGLTexture2D : public Texture
	{
	public:
		OpenGLTexture2D(std::string& path);
		virtual ~OpenGLTexture2D();

		virtual uint32_t GetWidth() const override { return m_Width; }
		virtual uint32_t GetHeight() const override { return m_Height; };

		virtual uint32_t Bind(uint32_t slot = 0) const override;

	private:
		std::string m_Path;
		uint32_t m_RenderId;
		uint32_t m_Width, m_Height;
	};
}
