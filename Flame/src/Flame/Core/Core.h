#pragma once

#include <memory>

#ifdef  FL_PLATFORM_WINDOWS
	#ifdef FL_DYNAMIC_LINK
		#ifdef FL_BUILD_DLL
			#define FLAME_API __declspec(dllexport)
		#else
			#define FLAME_API __declspec(dllimport)
		#endif
	#else
		#define FLAME_API
	#endif
#else
	#error Flame only support Windows!
#endif

#ifdef FL_ENABLE_ASSERTS
	#define FL_ASSERT(x, ...) { if(!(x)) { FL_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
	#define FL_CORE_ASSERT(x, ...) { if(!(x)) { FL_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
	#define FL_ASSERT(x, ...)
	#define FL_CORE_ASSERT(x, ...)
#endif

#define BIT(x) (1 << x)

#define FL_BIND_EVENT_FN(fn) [this](auto&&... args) -> decltype(auto) { return this->fn(std::forward<decltype(args)>(args)...); }

namespace flame
{
	template<typename T>
	using Scope = std::unique_ptr<T>;

	template<typename T>
	using Ref = std::shared_ptr<T>;
}