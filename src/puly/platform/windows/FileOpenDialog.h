#pragma once

#include <string>
#include <nfd.h>
#include "../../lowlevel/debugging/Log.h"

namespace Puly {

	static std::string openfilename() {
		nfdchar_t* outPath = NULL;
		nfdresult_t result = NFD_OpenDialog(NULL, NULL, &outPath);

		if (result == NFD_OKAY) {
			return outPath;
		}
		else if (result == NFD_CANCEL) {
			PL_LOG_INFO("File load cancelled");
			return "";
		}
		else {
			PL_LOG_ERROR("Couldn't open this file, error: {}", NFD_GetError());
			return "";
		}

		return "";
	}

	static std::string savefile(const nfdchar_t* filter) {
		nfdchar_t* outPath = NULL;
		nfdresult_t result = NFD_SaveDialog(filter, NULL, &outPath);

		if (result == NFD_OKAY) {
			return outPath;
		}
		else {
			PL_LOG_ERROR("Couldn't save this file, error: {}", NFD_GetError());
			return "";
		}

		return "";
	}

}