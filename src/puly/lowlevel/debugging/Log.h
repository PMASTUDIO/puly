#pragma once

#include "spdlog/spdlog.h"

namespace Puly {

	class Log {
	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetLogger() { return s_Logger; }

	private:
		static std::shared_ptr<spdlog::logger> s_Logger;
	};

}

#define PL_LOG_ERROR(...) ::Puly::Log::GetLogger()->error(__VA_ARGS__)
#define PL_LOG_WARN(...) ::Puly::Log::GetLogger()->warn(__VA_ARGS__)
#define PL_LOG_INFO(...) ::Puly::Log::GetLogger()->trace(__VA_ARGS__)
#define PL_LOG_SUCCESS(...) ::Puly::Log::GetLogger()->info(__VA_ARGS__)