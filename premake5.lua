workspace "Flame"
    architecture "x64"
    startproject "Sandbox"

    configurations
    {
        "Debug",
        "Release",
        "Dist"
    }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

--Include directories relative to root folder(solution directory)
IncludeDir = {}
IncludeDir["glfw"] = "Flame/vendor/glfw/include"
IncludeDir["glad"] = "Flame/vendor/glad/include"
IncludeDir["imgui"] = "Flame/vendor/imgui"
IncludeDir["glm"] = "Flame/vendor/glm"
IncludeDir["stb_image"] = "Flame/vendor/stb_image"

include "Flame/vendor/glfw"
include "Flame/vendor/glad"
include "Flame/vendor/imgui"

project "Flame"
    location "Flame"
    kind "StaticLib"
    language "C++"
    cppdialect "C++17"
    staticruntime "on"

    targetdir("bin/" .. outputdir .. "/%{prj.name}")
    objdir("bin/int/" .. outputdir .. "/%{prj.name}")

    pchheader "flpch.h"
    pchsource "%{prj.name}/src/flpch.cpp"

    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp",
        "%{prj.name}/vendor/stb_image/**.h",
		"%{prj.name}/vendor/stb_image/**.cpp",
        "%{prj.name}/vendor/glm/glm/**.hpp",
        "%{prj.name}/vendor/glm/glm/**.inl"
    }

    defines
    {
        "_CRT_SECURE_NO_WARNINGS"
    }

    includedirs
    {
        "%{prj.name}/src",
        "%{prj.name}/vendor/spdlog/include",
        "%{IncludeDir.glfw}",
        "%{IncludeDir.glad}",
        "%{IncludeDir.imgui}",
        "%{IncludeDir.glm}",
        "%{IncludeDir.stb_image}"
    }

    links
    {
        "GLFW",
        "GLAD",
        "ImGui",
        "opengl32.lib"
    }

    filter "system:windows"
        systemversion "latest"

        defines 
        {
           "FL_PLATFORM_WINDOWS",
           "FL_BUILD_DLL",
           "FL_DYNAMIC_LINK",
           "FL_ENABLE_ASSERTS",
           "GLFW_INCLUDE_NONE"
        }
    
    filter "configurations:Debug"
        defines "FL_DEBUG"
        runtime "Debug"
        symbols "on"

    filter "configurations:Release"
        defines "FL_RELEASE"
        runtime "Release"
        optimize "on"

    filter "configurations:Dist"
        defines "FL_DIST"
        runtime "Release"
        optimize "on"

project "Sandbox"
    location "Sandbox"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"
    staticruntime "on"

    targetdir("bin/" .. outputdir .. "/%{prj.name}")
    objdir("bin/int/" .. outputdir .. "/%{prj.name}")

    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp"
    }

    includedirs
    {
        "Flame/vendor/spdlog/include",
        "Flame/src",
        "Flame/vendor",
        "%{IncludeDir.glm}"
    }

    links
    {
        "Flame"
    }

    filter "system:windows"
        systemversion "latest"

        defines 
        {
           "FL_PLATFORM_WINDOWS"
        }
    
    filter "configurations:Debug"
        defines "FL_DEBUG"
        runtime "Debug"
        symbols "on"

    filter "configurations:Release"
        defines "FL_RELEASE"
        runtime "Release"
        optimize "on"

    filter "configurations:Dist"
        defines "FL_DIST"
        runtime "Release"
        optimize "on"