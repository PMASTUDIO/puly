#pragma once

#include <string>
#include "GL/glew.h"

#include <glm/glm.hpp>

#include <unordered_map>

namespace Puly {
	class Shader
	{
	public:
		Shader();
		~Shader();

		void Compile(const std::string& vertexSource, const std::string& fragmentSource);

		void Bind();
		void Unbind();

		void UploadUniform1i(const std::string& name, int value);

		void UploadUniformFloat(const std::string& name, const float v0);
		void UploadUniformFloat2(const std::string& name, const float v0, const float v1);
		void UploadUniformFloat3(const std::string& name, const float v0, const float v1, const float v2);
		void UploadUniformFloat4(const std::string& name, const float v0, const float v1, const float v2, const float v3);
		
		void UploadUniformMat3(const std::string& name, const glm::mat3& matrix);
		void UploadUniformMat4(const std::string& name, const glm::mat4& matrix);
	private:
		void CheckCompileErrors(GLuint object, std::string type);
		GLint GetUniformLocation(const std::string& name);
	private:
		uint32_t m_ShaderID;
		std::unordered_map<std::string, GLint> m_UniformLocationCache;
	};
}
