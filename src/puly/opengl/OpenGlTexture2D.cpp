#include "OpenGlTexture2D.h"

#include "SOIL2/SOIL2.h"
#include "..//lowlevel/debugging/Log.h"


Puly::OpenGLTexture2D::OpenGLTexture2D(std::string& path) : m_Path(path)
{
	int width, height, channels;

	//stbi_set_flip_vertically_on_load(1);
	//unsigned char* data = SOIL_load_image(path.c_str(), &width, &height, &channels, 0);

	m_RenderId = SOIL_load_OGL_texture(path.c_str(), SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID,
		SOIL_FLAG_INVERT_Y);

	/*
	if (data == nullptr) {
		PL_LOG_ERROR("Error with STBI loading image: {}", path);
		return;
	}
	*/

	if (0 == m_RenderId) {
		PL_LOG_ERROR("Error with SOIL loading image: {}", path);
		return;
	}

	/*m_Width = width;
	m_Height = height;*/

	//glCreateTextures(GL_TEXTURE_2D, 1, &m_RenderId);
	//glTextureStorage2D(m_RenderId, 1, GL_RGBA16F, m_Width, m_Height);

	glTexParameteri(m_RenderId, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(m_RenderId, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	/*

	glTextureSubImage2D(m_RenderId, 0, 0, 0, m_Width, m_Height, GL_RGB, GL_UNSIGNED_BYTE, data);*/

	//stbi_image_free(data);
}

Puly::OpenGLTexture2D::~OpenGLTexture2D()
{
	glDeleteTextures(1, &m_RenderId);
}

uint32_t Puly::OpenGLTexture2D::Bind(uint32_t slot) const
{
	glBindTextureUnit(slot, m_RenderId);
	return m_RenderId;
}
