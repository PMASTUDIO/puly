#include "OpenGlTexture2D.h"

Puly::Texture2D::Texture2D() : m_Width(0), m_Height(0), m_Image_Format(GL_RGBA), m_Internal_Format(GL_RGBA), m_Wrap_S(GL_REPEAT)
							  ,m_Wrap_T(GL_REPEAT), m_Filter_Min(GL_LINEAR), m_Filter_Max(GL_LINEAR)
{
	glGenTextures(1, &this->m_RenderId);
}

void Puly::Texture2D::Generate(unsigned int width, unsigned int height, unsigned char* data)
{
	this->m_Width = width;
	this->m_Height = height;

	glBindTexture(GL_TEXTURE_2D, this->m_RenderId);
	glTexImage2D(GL_TEXTURE_2D, 0, this->m_Internal_Format, this->m_Width, this->m_Height, 0, this->m_Image_Format, GL_UNSIGNED_BYTE, data);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, this->m_Wrap_S);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, this->m_Wrap_T);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, this->m_Filter_Min);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, this->m_Filter_Max);

	glBindTexture(GL_TEXTURE_2D, 0);
}

void Puly::Texture2D::Bind() const
{
	glBindTexture(GL_TEXTURE_2D, this->m_RenderId);
}

void Puly::Texture2D::Unbind() const
{
	glBindTexture(GL_TEXTURE_2D, 0);
}

unsigned int Puly::Texture2D::GetRendererId() const
{
	return m_RenderId;
}
