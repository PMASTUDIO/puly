#pragma once

#include <string>
#include "GL/glew.h"

namespace Puly {
	class Shader
	{
	public:
		Shader(const std::string& vertexSource, const std::string& fragmentSource);
		~Shader();

		void Bind();
		void Unbind();

	private:
		uint32_t m_ShaderID;

		void CheckCompileErrors(GLuint object, std::string type);
	};
}
