#pragma once

#include <string>
#include "GL/glew.h"

namespace Puly {
	class Shader
	{
	public:
		Shader();
		~Shader();

		void Compile(const std::string& vertexSource, const std::string& fragmentSource);

		void Bind();
		void Unbind();

	private:
		uint32_t m_ShaderID;

		void CheckCompileErrors(GLuint object, std::string type);
	};
}
