#pragma once

#include <string>
#include "GL/glew.h"

#include <glm/glm.hpp>

namespace Puly {
	class Shader
	{
	public:
		Shader();
		~Shader();

		void Compile(const std::string& vertexSource, const std::string& fragmentSource);

		void Bind();
		void Unbind();

		void UploadUniformMat4(const std::string& name, const glm::mat4& matrix);
		void UploadUniform1i(const std::string& name, int value);
	private:
		uint32_t m_ShaderID;

		void CheckCompileErrors(GLuint object, std::string type);
	};
}
