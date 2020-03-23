workspace "Game Engine"
	language "C++"
	architecture "x86_64"
	configurations { "Debug", "Release" }
	cppdialect 'C++17' 

	filter { "configurations:Debug" }
        runtime "Debug"
        symbols "On"
		defines { "JAM_DEBUG" }
	
	filter { "configurations:Release" }
        runtime "Release"
        optimize "On"
		defines { "NDEBUG", "JAM_RELEASE" }
	filter { }
	
	targetdir ("bin/%{cfg.longname}")
    objdir ("obj/%{cfg.longname}")

    
project "Jam-Engine"
	kind "ConsoleApp"
	
	pchheader "jampch.h"
	pchsource "src/jampch.cpp"

	files "src/**"

	defines {"ALUT_STATIC"}

	includedirs { "./src/", "./modules/glm/", "./modules/physfs/src/", "./modules/fmt/include/", "./modules/rlutil/", "./modules/openal-soft/include/", "./modules/openal-soft/include/AL/", "./modules/freealut/include/", "./modules/glfw/include/",  "./modules/glad/%{cfg.longname}/include" }
	
	libdirs {"deps/glfw/%{cfg.longname}/", "deps/physfs/%{cfg.longname}/", "deps/fmt/%{cfg.longname}/", "deps/openal-soft/%{cfg.longname}/", "deps/freealut/%{cfg.longname}/", "deps/glfw/%{cfg.longname}/", "deps/glad/%{cfg.longname}/" }
	
	links { "physfs-static.lib", "common.lib", "ex-common.lib", "OpenAL32.lib", "alut_static.lib", "glfw3.lib", "glad.lib" }

	filter { "configurations:Debug" }
		links { "fmtd.lib" }
	
	filter { "configurations:Release" }
		links { "fmt.lib" }
	
	filter { }


    filter {}