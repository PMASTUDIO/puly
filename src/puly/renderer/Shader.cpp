#include "Shader.h"
#include "GL/glew.h"

#include "..//lowlevel/debugging/Log.h"
#include <iostream>

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
