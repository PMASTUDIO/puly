#pragma once

#include "spdlog/spdlog.h"

namespace Puly {

	typedef spdlog::level::level_enum VERBOSITY_LEVEL;

	class Log {
	public:
		static void Init(int level);

		inline static std::shared_ptr<spdlog::logger>& GetLogger() { return s_Logger; }

	private:
		static std::shared_ptr<spdlog::logger> s_Logger;
	};

}

#define PL_LOG_ERROR(...) ::Puly::Log::GetLogger()->error(__VA_ARGS__)
#define PL_LOG_WARN(...) ::Puly::Log::GetLogger()->warn(__VA_ARGS__)
#define PL_LOG_INFO(...) ::Puly::Log::GetLogger()->trace(__VA_ARGS__)
#define PL_LOG_SUCCESS(...) ::Puly::Log::GetLogger()->info(__VA_ARGS__)

#define LEVEL_INFO spdlog::level::trace
#define LEVEL_SUCCESS spdlog::level::info
#define LEVEL_WARNING spdlog::level::warn
#define LEVEL_ERROR spdlog::level::err