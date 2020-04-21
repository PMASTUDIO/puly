#pragma once

#include <GL/glew.h>

namespace Puly {
	class Texture2D {
	public:
		Texture2D();

		void Generate(unsigned int width, unsigned int height, unsigned char* data);

		void Bind() const;
		void Unbind() const;

		unsigned int GetRendererId() const;

	private:
		GLuint m_RenderId;
		GLuint m_Width, m_Height;

		// Texture Format
		GLuint m_Internal_Format;
		GLuint m_Image_Format;

		// Texture configuration
		GLuint m_Wrap_S;
		GLuint m_Wrap_T;
		GLuint m_Filter_Min;
		GLuint m_Filter_Max;
	};
}
