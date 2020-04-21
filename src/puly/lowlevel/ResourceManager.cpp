#include "ResourceManager.h"

#include <sstream>
#include <fstream>

#include "debugging/Log.h"

namespace Puly {
	std::map<std::string, Texture2D> ResourceManager::m_Textures;

	/*
	std::map<std::string, Shader> ResourceManager::Shaders;
	
	Shader ResourceManager::LoadShader(std::string vShaderFile, std::string fShaderFile, std::string name)
	{
		Shaders[name] = loadShaderFromFile(vShaderFile, fShaderFile);
		return Shaders[name];
	}

	Shader ResourceManager::GetShader(std::string name)
	{
		return Shaders[name];
	}
	*/

	Texture2D ResourceManager::LoadTexture(const GLchar* file, GLboolean alpha, std::string name)
	{
		m_Textures[name] = LoadTextureFromFile(file, alpha);
		return m_Textures[name];
	}

	Texture2D ResourceManager::GetTexture(std::string name)
	{
		return m_Textures[name];
	}

	std::tuple<std::string, std::string> ResourceManager::GetShaderText(std::string vShaderFile, std::string fShaderFile)
	{
		std::string vertexCode;
		std::string fragmentCode;

		try
		{
			// Open files
			std::ifstream vertexShaderFile(vShaderFile);
			std::ifstream fragmentShaderFile(fShaderFile);
			std::stringstream vShaderStream, fShaderStream;
			// Read file's buffer contents into streams
			vShaderStream << vertexShaderFile.rdbuf();
			fShaderStream << fragmentShaderFile.rdbuf();
			// close file handlers
			vertexShaderFile.close();
			fragmentShaderFile.close();
			// Convert stream into string
			vertexCode = vShaderStream.str();
			fragmentCode = fShaderStream.str();
		}
		catch (std::exception e)
		{
			PL_LOG_ERROR("ERROR::SHADER: Failed to read shader files");
		}

		return std::make_tuple(vertexCode, fragmentCode);
	}

	void ResourceManager::Clear()
	{
		for (auto iter : m_Textures)
			glDeleteTextures(1, (const GLuint*)iter.second.GetRendererId());
	}

	Texture2D ResourceManager::LoadTextureFromFile(const GLchar* file, GLboolean alpha)
	{
		return Texture2D();
	}
	/*
	Shader ResourceManager::loadShaderFromFile(std::string vShaderFile, std::string fShaderFile)
	{
		std::string vertexCode;
		std::string fragmentCode;

		try
		{
			// Open files
			std::ifstream vertexShaderFile(vShaderFile);
			std::ifstream fragmentShaderFile(fShaderFile);
			std::stringstream vShaderStream, fShaderStream;
			// Read file's buffer contents into streams
			vShaderStream << vertexShaderFile.rdbuf();
			fShaderStream << fragmentShaderFile.rdbuf();
			// close file handlers
			vertexShaderFile.close();
			fragmentShaderFile.close();
			// Convert stream into string
			vertexCode = vShaderStream.str();
			fragmentCode = fShaderStream.str();
		}
		catch (std::exception e)
		{
			PL_LOG_ERROR("ERROR::SHADER: Failed to read shader files");
		}

		Shader m_Shader;
		m_Shader.Compile(vertexCode, fragmentCode);

		return m_Shader;
	}
	*/
}