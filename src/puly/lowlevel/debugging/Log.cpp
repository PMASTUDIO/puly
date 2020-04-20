#include "Log.h"
#include "spdlog/sinks/stdout_color_sinks.h"


namespace Puly {

	std::shared_ptr<spdlog::logger> Log::s_Logger;

}

void Puly::Log::Init(int level)
{
	VERBOSITY_LEVEL currentLevel = LEVEL_INFO;

	switch (level)
	{
	case 0:
		currentLevel = LEVEL_INFO;
		break;
	case 1:
		currentLevel = LEVEL_SUCCESS;
		break;
	case 2:
		currentLevel = LEVEL_WARNING;
		break;
	case 3:
		currentLevel = LEVEL_ERROR;
		break;
	default:
		break;
	}

	spdlog::set_pattern("%^ [%T]: %v%$");

	s_Logger = spdlog::stdout_color_mt("PULY");
	s_Logger->set_level(currentLevel);
}
