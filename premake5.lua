require "Vendor/Premake/export-compile-commands"

workspace "PixelLands"
	architecture "x64"

	configurations
	{
		"Debug",
		"Release",
		"Distribution"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"


project "PixelLands"
	kind "ConsoleApp"
	language "C"
	targetdir ("Binaries/" .. outputdir .. "/%{prj.name}")
	objdir ("Intermediates/" .. outputdir .. "/%{prj.name}")

	files 
	{
		"%{prj.name}/Source/**.h",
		"%{prj.name}/Source/**.c",
		"Vendor/Include/GLAD/glad.c"
	}

	includedirs
    {
        "Vendor/Include"
    }

	libdirs
	{
		"Vendor/Lib"
	}

	links 
	{
		"glfw3",
		"cglm"
	}

	linkoptions { "-static" }


	filter "system:windows"
		staticruntime "On"
		systemversion "latest"

		buildoptions 
		{ 
			"-fdiagnostics-color=always" 
		}

		links
        {
            "opengl32",
			"gdi32"
        }


	filter "configurations:Debug"
		defines "SPG_DEBUG"
		symbols "On"
	
	filter "configurations:Release"
		defines "SPG_RELEASE"
		optimize "On"
	
	filter "configurations:Distribution"
		defines "SPG_DISTRIBUTION"
		optimize "On"

