#include "Scene.h"
#include <list>

Puly::SceneConfig::SceneConfig(std::string sceneName) : m_SceneName(sceneName), sceneFile(true, false, true), filePath("")
{
}

Puly::SceneConfig::~SceneConfig()
{
}

bool Puly::SceneConfig::Init()
{

	if (!LoadFile(filePath.c_str())) {
		return false;
	}

	return true;
}

void Puly::SceneConfig::Shutdown()
{
	sceneFile.SaveFile(filePath.c_str());
}

bool Puly::SceneConfig::LoadFile(const char* filePath)
{
	SI_Error rc = sceneFile.LoadFile(filePath);

	if (rc < 0) {
		return false;
	}

	return true;
}

const char* Puly::SceneConfig::GetValue(const char* section, const char* keyName)
{
	return sceneFile.GetValue(section, keyName, NULL);
}

bool Puly::SceneConfig::SetValue(const char* section, const char* key, const char* value)
{
	SI_Error rc = sceneFile.SetValue(section, key, value);
	
	if (rc < 0) return false;

	return true;
}

bool Puly::SceneConfig::Delete(const char* section, const char* key)
{
	bool success = sceneFile.Delete(section, key);

	if (!success) return false;

	return true;
}

void Puly::SceneConfig::SetFilePath(std::string filePath)
{
	this->filePath = filePath;
}
