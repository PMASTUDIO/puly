#pragma once

#include <map>
#include <memory>
#include <string>

#include "..//renderer/Shader.h"

#include "..//opengl/OpenGlTexture2D.h"

namespace Puly {

	class ResourceManager {
	public:
		static std::shared_ptr<Shader> LoadShader(std::string vertexShaderPath, std::string fragmentShaderPath);
		static std::shared_ptr<Shader> GetShader(std::string vertexShaderPath, std::string fragmentShaderPath);

		static std::shared_ptr<Texture> LoadTexture(const char* file);
		static std::shared_ptr<Texture> GetTexture(std::string name);

		static std::tuple<std::string, std::string> GetShaderText(std::string vShaderFile, std::string fShaderFile);

		static void Clear();
	private:
		static std::map<std::string, std::shared_ptr<Texture>> m_Textures;
		
		//static Texture2D LoadTextureFromFile(const GLchar* file, GLboolean alpha);

		static std::map<std::string, std::shared_ptr<Shader>> m_Shaders;

		//static Shader loadShaderFromFile(std::string vShaderFile, std::string fShaderFile);
	};

}