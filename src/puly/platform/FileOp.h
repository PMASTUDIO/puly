#pragma once

#include <exception>
#include <filesystem>
#include "..//lowlevel/debugging/Log.h"

namespace fs = std::experimental::filesystem;

namespace Puly {

	void copyFile(fs::path srcFile, fs::path destFolder)
	{
		auto target = destFolder / srcFile.filename();

		try // If you want to avoid exception handling, then use the error code overload of the following functions.
		{
			fs::create_directories(destFolder); // Recursively create target directory if not existing.
			fs::copy_file(srcFile, target, fs::copy_options::overwrite_existing);
		}
		catch (std::exception& e) // Not using fs::filesystem_error since std::bad_alloc can throw too.  
		{
			PL_LOG_ERROR("Error moving file: {}", e.what());
		}
	}

}