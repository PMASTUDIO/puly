#pragma once

#include <map>
#include <string>

#include "..//renderer/Shader.h"

namespace Puly {

	class ResourceManager {
	public:
		//static Shader LoadShader(std::string vShaderFile, std::string fShaderFile, std::string name);
		//static Shader GetShader(std::string name);

		static std::tuple<std::string, std::string> GetShaderText(std::string vShaderFile, std::string fShaderFile);

		static void Clear();
	private:
		//static std::map<std::string, Shader> Shaders;

		//static Shader loadShaderFromFile(std::string vShaderFile, std::string fShaderFile);
	};

}