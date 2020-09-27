#pragma once
#include "Application.h"

#ifdef FL_PLATFORM_WINDOWS

extern flame::Application* flame::CreateApplication();

int main(int argc, char** argv)
{
	flame::Log::Init();
	FL_CORE_WARN("Initialized Log!");
	
	auto* app = flame::CreateApplication();
	app->Run();
	delete app;
}

#endif