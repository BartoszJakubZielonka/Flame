#pragma once
#include "Application.h"

#ifdef FL_PLATFORM_WINDOWS

extern flame::Application* flame::CreateApplication();

int main(int argc, char** argv)
{
	flame::Log::Init();

	FL_PROFILE_BEGIN_SESSION("Startup", "FlameProfile-Startup.json");
	auto* app = flame::CreateApplication();
	FL_PROFILE_END_SESSION();

	FL_PROFILE_BEGIN_SESSION("Runtime", "FlameProfile-Runtime.json");
	app->Run();
	FL_PROFILE_END_SESSION();

	FL_PROFILE_BEGIN_SESSION("Shutdown", "FlameProfile-Shutdown.json");
	delete app;
	FL_PROFILE_END_SESSION();
}

#endif