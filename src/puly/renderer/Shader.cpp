#include "Shader.h"
#include "GL/glew.h"

#include "..//lowlevel/debugging/Log.h"
#include <iostream>

#include <glm/gtc/type_ptr.hpp>

Puly::Shader::Shader()
{
}

Puly::Shader::~Shader()
{
	glDeleteProgram(m_ShaderID);
}

void Puly::Shader::Compile(const std::string& vertexSource, const std::string& fragmentSource)
{
	GLuint sVertex, sFragment;

	const GLchar* vertexSrc = vertexSource.c_str();
	const GLchar* fragSrc = fragmentSource.c_str();

	// Vertex Shader
	sVertex = glCreateShader(GL_VERTEX_SHADER);

	glShaderSource(sVertex, 1, &vertexSrc, NULL);
	glCompileShader(sVertex);

	CheckCompileErrors(sVertex, "VERTEX");

	// Fragment Shader
	sFragment = glCreateShader(GL_FRAGMENT_SHADER);

	glShaderSource(sFragment, 1, &fragSrc, NULL);
	glCompileShader(sFragment);

	CheckCompileErrors(sFragment, "FRAGMENT");

	// Shader Program
	this->m_ShaderID = glCreateProgram();

	glAttachShader(this->m_ShaderID, sVertex);
	glAttachShader(this->m_ShaderID, sFragment);

	glLinkProgram(this->m_ShaderID);

	// Delete the shaders as they're linked into our program now and no longer necessery
	glDeleteShader(sVertex);
	glDeleteShader(sFragment);

}

void Puly::Shader::Bind()
{
	glUseProgram(this->m_ShaderID);
}

void Puly::Shader::Unbind()
{
	glUseProgram(0);
}

void Puly::Shader::UploadUniformFloat(const std::string& name, const float v0)
{
	GLint location = GetUniformLocation(name);
	glUniform1f(location, v0);
}

void Puly::Shader::UploadUniformFloat2(const std::string& name, const float v0, const float v1)
{
	GLint location = GetUniformLocation(name);
	glUniform2f(location, v0, v1);
}

void Puly::Shader::UploadUniformFloat3(const std::string& name, const float v0, const float v1, const float v2)
{
	GLint location = GetUniformLocation(name);
	glUniform3f(location, v0, v1, v2);
}

void Puly::Shader::UploadUniformFloat4(const std::string& name, const float v0, const float v1, const float v2, const float v3)
{
	GLint location = GetUniformLocation(name);
	glUniform4f(location, v0, v1, v2, v3);
}

void Puly::Shader::UploadUniformMat3(const std::string& name, const glm::mat3& matrix)
{
	GLint location = GetUniformLocation(name);
	glUniformMatrix3fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
}

void Puly::Shader::UploadUniformMat4(const std::string& name, const glm::mat4& matrix)
{
	GLint location = GetUniformLocation(name);
	glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
}

void Puly::Shader::UploadUniform1i(const std::string& name, int value)
{
	GLint location = GetUniformLocation(name);
	glUniform1i(location, value);
}

void Puly::Shader::CheckCompileErrors(GLuint object, std::string type)
{
	GLint success;
	GLchar infoLog[1024];
	if (type != "PROGRAM")
	{
		glGetShaderiv(object, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(object, 1024, NULL, infoLog);
			Log::GetLogger()->error("ERROR::SHADER: Compile-time error: Type: {} - {}", type, infoLog);
		}
	}
	else
	{
		glGetProgramiv(object, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(object, 1024, NULL, infoLog);
			Log::GetLogger()->error("ERROR::Shader: Link-time error: Type: {} - {}", type, infoLog);
		}
	}
}

GLint Puly::Shader::GetUniformLocation(const std::string& name)
{
	if (m_UniformLocationCache.find(name) != m_UniformLocationCache.end())
		return m_UniformLocationCache[name];


	GLint location = glGetUniformLocation(m_ShaderID, name.c_str());

	if (location == -1) {
		PL_LOG_WARN("Uniform '{0}' not found!", name);
		return location;
	}

	m_UniformLocationCache[name] = location;
	return location;
}
