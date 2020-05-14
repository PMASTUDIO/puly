#include "ResourceManager.h"

#include <sstream>
#include <fstream>

#include "debugging/Log.h"
#include <SOIL2/SOIL2.h>

namespace Puly {
	std::map<std::string, std::shared_ptr<Texture>> ResourceManager::m_Textures;

	
	//std::map<std::string, Shader> ResourceManager::Shaders;
	/*
	Shader ResourceManager::LoadShader(std::string vShaderFile, std::string fShaderFile, std::string name)
	{
		Shaders[name] = loadShaderFromFile(vShaderFile, fShaderFile);
		return Shaders[name];
	}*/

	/*std::shared_ptr<Texture> ResourceManager::GetShader(std::string name)
	{
		return Shaders[name];
	}*/
	

	std::shared_ptr<Texture> ResourceManager::LoadTexture(const char* file)
	{
		m_Textures[file] = Puly::Texture2D::Create(file);
		return m_Textures[file];
	}

	std::shared_ptr<Texture> ResourceManager::GetTexture(std::string name)
	{
		if (m_Textures.find(name) == m_Textures.end()) {
			return LoadTexture(name.c_str());
		}
		
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
	}

	/*

	Texture2D ResourceManager::LoadTextureFromFile(const GLchar* file, GLboolean alpha)
	{
		Texture2D texture;
		if (alpha) {
			texture.SetImageFormat(GL_RGBA);
			texture.SetInternalFormat(GL_RGBA);
		}
		int width, height;
		unsigned char* image = SOIL_load_image(file, &width, &height, 0,
			texture.SetImageFormat(GL_RGBA ? SOIL_LOAD_RGBA : SOIL_LOAD_RGB));

		texture.Generate(width, height, image);

		SOIL_free_image_data(image);
		return texture;
	}
	
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