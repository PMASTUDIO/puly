#include "Scene.h"

Puly::SceneConfig::SceneConfig(std::string sceneName) : m_SceneName(sceneName), sceneFile(true, false, true), filePath("")
{
}

Puly::SceneConfig::~SceneConfig()
{
}

bool Puly::SceneConfig::Init()
{

	if (!LoadFile(m_SceneName.c_str())) {
		return false;
	}

	return true;
}

void Puly::SceneConfig::Shutdown()
{
	sceneFile.SaveFile(m_SceneName.c_str());
}

std::vector<std::string> Puly::SceneConfig::GetComponentsInObject(std::string objDebuggingName)
{
	CSimpleIniA::TNamesDepend sections;
	sceneFile.GetAllSections(sections);

	std::vector<std::string> sectionNames;

	CSimpleIniA::TNamesDepend::const_iterator i;
	for (i = sections.begin(); i != sections.end(); ++i)
	{
		std::string name(i->pItem);
		char nameFirstChar = name.at(0);
		char objectIdentifier = ':';

		if (nameFirstChar == objectIdentifier) {
			// Check if component is in this object return section name
			std::size_t posName = name.find(objDebuggingName);
			if (posName != std::string::npos) {
				sectionNames.push_back(i->pItem);
			}
		}
	}

	return sectionNames;
}

std::vector<std::string> Puly::SceneConfig::GetObjects()
{
	CSimpleIniA::TNamesDepend sections;
	sceneFile.GetAllSections(sections);

	std::vector<std::string> sectionNames;

	CSimpleIniA::TNamesDepend::const_iterator i;
	for (i = sections.begin(); i != sections.end(); ++i)
	{
		std::string name(i->pItem);
		char nameFirstChar = name.at(0);
		char objectIdentifier = ':';

		if (nameFirstChar != objectIdentifier) {
			sectionNames.push_back(i->pItem);
		}
	}

	return sectionNames;
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
