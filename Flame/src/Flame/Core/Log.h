#pragma once

#include "Core.h"

#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>

namespace flame
{

	class FLAME_API Log
	{
	public:
		Log() = default;
		~Log() = default;

		static void Init();

		inline static Ref < spdlog::logger > & GetCoreLogger();
		inline static Ref < spdlog::logger > & GetClientLogger();
	private:
		static Ref<spdlog::logger> s_CoreLogger;
		static Ref<spdlog::logger> s_ClientLogger;
	};

}

//Core log macros
#define FL_CORE_TRACE(...) ::flame::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define FL_CORE_INFO(...) ::flame::Log::GetCoreLogger()->info(__VA_ARGS__)
#define FL_CORE_WARN(...) ::flame::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define FL_CORE_ERROR(...) ::flame::Log::GetCoreLogger()->error(__VA_ARGS__)
#define FL_CORE_FATAL(...) ::flame::Log::GetCoreLogger()->fatal(__VA_ARGS__)

//Client log macros
#define FL_TRACE(...) ::flame::Log::GetClientLogger()->trace(__VA_ARGS__)
#define FL_INFO(...) ::flame::Log::GetClientLogger()->info(__VA_ARGS__)
#define FL_WARN(...) ::flame::Log::GetClientLogger()->warn(__VA_ARGS__)
#define FL_ERROR(...) ::flame::Log::GetClientLogger()->error(__VA_ARGS__)
#define FL_FATAL(...) ::flame::Log::GetClientLogger()->fatal(__VA_ARGS__)