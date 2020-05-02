
workspace "LoggerScorpio"

	architecture "x64"

	configurations 
	{ 
		"Debug", 
		"Release", 
		"ReleaseNoLog"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "LoggerScorpio"

	location "%{prj.name}"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++14"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files 
	{ 
		"%{prj.name}/src/**.h", 
		"%{prj.name}/src/**.c" 
	}

	
	filter "system:windows"
		systemversion "latest"

	filter "configurations:Debug"
		defines { "DEBUG" }
		symbols "On"

    filter "configurations:Release"
		defines { "RELEASE" }
		optimize "On"

	filter "configurations:ReleaseNoLog"
		defines { "RELEASE", "NOLOG"}
		optimize "On"
	