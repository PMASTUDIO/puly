#pragma once

#include <string>
#include "..//lowlevel/iniParser/SimpleIni.h"

namespace Puly {
	class SceneConfig {
	public:
		SceneConfig(std::string sceneName);
		~SceneConfig();

		bool Init();
		void Shutdown();

		const char* GetValue(const char* section, const char* keyName);
		bool SetValue(const char* section, const char* key, const char* value);
		bool Delete(const char* section, const char* key);

		std::string GetFilePath() const { return filePath; }
		void SetFilePath(std::string filePath);

	private:
		CSimpleIniA sceneFile;
		
		bool LoadFile(const char * filePath);

		std::string filePath;
		std::string m_SceneName;
	};

	class GameLevel {
	public:
		GameLevel(std::string name) : configurator(name) { 
			configurator.SetFilePath(name);
		}
		~GameLevel() { configurator.Shutdown(); }
	public:
		SceneConfig configurator;
		//void Create(std::string levelName);
	};
}
