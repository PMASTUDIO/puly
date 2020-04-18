#pragma once

#include "..//lowlevel/iniParser/SimpleIni.h"

namespace Puly {
	class Configurations {
	public:
		Configurations();
		~Configurations();

		bool Init();
		void Shutdown();

		const char* GetValue(const char* keyName);
		bool SetValue(const char* key, const char* value);
		bool Delete(const char* key);

		const char* GetFilePath() const { return filePath; }
		void SetFilePath(const char* filePath);

	private:
		CSimpleIniA configFile;
		
		bool LoadFile(const char * filePath);
		const char* filePath;
	};
}