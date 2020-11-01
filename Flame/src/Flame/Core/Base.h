#pragma once

#include <memory>

// Platform detection using predefined macros.
#ifdef _WIN32
	// Windows x64/x86
	#ifdef _WIN64
		#define FL_PLATFORM_WINDOWS
	#else
		#error "x86 Builds are not supported!"
	#endif
#endif // End of platform detection

#ifdef FL_DEBUG
	#if defined(FL_PLATFORM_WINDOWS)
		#define FL_DEBUGBREAK() __debugbreak()
	#else
		#error "Platform doesn't support debugbreak yet!"
	#endif
	#define FL_ENABLE_ASSERTS
#else
	#define FL_DEBUGBREAK()
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
	template<typename T, typename ... Args>
	constexpr Scope<T> CreateScope(Args&& ... args)
	{
		return std::make_unique<T>(std::forward<Args>(args)...);
	}

	template<typename T>
	using Ref = std::shared_ptr<T>;
	template<typename T, typename ... Args>
	constexpr Ref<T> CreateRef(Args&& ... args)
	{
		return std::make_shared<T>(std::forward<Args>(args)...);
	}
}