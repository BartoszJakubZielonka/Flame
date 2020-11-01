#include "flpch.h"
#include "Flame/Core/Input.h"

#ifdef FL_PLATFORM_WINDOWS
	#include "Platform/Windows/WindowsInput.h"
#endif

namespace flame {

	Scope<Input> Input::s_Instance = Input::Create();

	Scope<Input> Input::Create()
	{
	#ifdef FL_PLATFORM_WINDOWS
		return CreateScope<WindowsInput>();
	#else
		FL_CORE_ASSERT(false, "Unknown platform!");
		return nullptr;
	#endif
	}
} 