#include "Log.h"
#include "spdlog/sinks/stdout_color_sinks.h"


namespace Puly {

	std::shared_ptr<spdlog::logger> Log::s_Logger;

}

void Puly::Log::Init()
{
	spdlog::set_pattern("%^ [%T]: %v%$");

	s_Logger = spdlog::stdout_color_mt("PULY");
	s_Logger->set_level(spdlog::level::trace);
}
