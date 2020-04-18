#include "Configuration.h"

Puly::Configurations::Configurations() : configFile(true, false, true)
{
	this->filePath = "resources/config/baseConfig.ini";
}

Puly::Configurations::~Configurations()
{
}

bool Puly::Configurations::Init()
{
	if (!LoadFile(filePath)) {
		return false;
	}

	return true;
}

void Puly::Configurations::Shutdown()
{
	configFile.SaveFile(filePath);
}

const char* Puly::Configurations::GetValue(const char* keyName)
{
	return configFile.GetValue("", keyName, NULL);
}

bool Puly::Configurations::SetValue(const char* key, const char* value)
{
	SI_Error rc = configFile.SetValue("", key, value);
	
	if (rc < 0) return false;

	return true;
}

bool Puly::Configurations::Delete(const char* key)
{
	bool success = configFile.Delete("", key);

	if (!success) return false;

	return true;
}

void Puly::Configurations::SetFilePath(const char* filePath)
{
	this->filePath = filePath;
}

bool Puly::Configurations::LoadFile(const char* file)
{
	SI_Error rc = configFile.LoadFile(file);

	if (rc < 0) {
		return false;
	}
	
	return true;
}
