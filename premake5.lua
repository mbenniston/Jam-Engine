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
	kind "StaticLib"
	staticruntime "on"	
	
	files "modules/imgui/examples/imgui_impl_opengl3.cpp"
	files "modules/imgui/examples/imgui_impl_glfw.cpp"
	files "modules/imgui/*.cpp"

	filter {"files:modules/imgui/**.cpp"}
		flags {"NoPCH"}
	filter {}

	filter {"files:src/stb/**.c"}
		flags {"NoPCH"}
	filter {}

	files "src/**"
	
	filter "system:Windows" 
		pchheader "jampch.h"
		pchsource "src/jampch.cpp"
	filter {}

	defines {"IMGUI_IMPL_OPENGL_LOADER_CUSTOM=\"../../modules/glad/%{cfg.longname}/include/glad/glad.h\""}

	-- includedirs { "./src/",  "./modules/glm", "./modules/imgui", "./modules/", "./modules/physfs/src/", "./modules/fmt/include/", "./modules/rlutil/", "./modules/openal-soft/include/", "./modules/openal-soft/include/AL/", "./modules/freealut/include/", "./modules/glfw/include/",  "./modules/glad/%{cfg.longname}/include" }
	-- any other includes that are not in the include directory are private includes and should not be used by anything else
	includedirs { "./src/", "./include", "./modules/imgui", "./modules/glfw/include/", "./modules/physfs/src/", "./modules/font8x8" }

	filter {"files:src/Gen/*.cpp"}
		flags {"NoPCH"}
	filter {}

	libdirs {"deps/glfw/%{cfg.longname}/", "deps/physfs/%{cfg.longname}/", "deps/fmt/%{cfg.longname}/", "deps/openal-soft/%{cfg.longname}/", "deps/freealut/%{cfg.longname}/", "deps/glfw/%{cfg.longname}/", "deps/glad/%{cfg.longname}/" }
	
	links { "physfs-static.lib", "common.lib", "ex-common.lib", "OpenAL32.lib", "alut_static.lib", "glfw3.lib", "glad.lib" }

	filter { "configurations:Debug" }
		links { "fmtd.lib" }
	
	filter { "configurations:Release" }
		links { "fmt.lib" }
	
	filter { }

	filter "system:windows" 
		postbuildcommands {
			"lib.exe /OUT:./bin/%{cfg.longname}/jengine.lib ./bin/%{cfg.longname}/Jam-Engine.lib ./deps/physfs/%{cfg.longname}/physfs-static.lib ./deps/openal-soft/%{cfg.longname}/common.lib ./deps/openal-soft/%{cfg.longname}/ex-common.lib ./deps/openal-soft/%{cfg.longname}/OpenAL32.lib ./deps/freealut/%{cfg.longname}/alut_static.lib ./deps/glfw/%{cfg.longname}/glfw3.lib ./deps/glad/%{cfg.longname}/glad.lib > nul 2>&1"
		}
	filter "system:linux"
		postbuildcommands {
			"ar -M < ./scriptsLinux/fat-lib-%{cfg.longname}.mri",
		}

    filter {}

project "Jam-Demo"
	kind "ConsoleApp"
	staticruntime "on"
	dependson { "Jam-Engine" }

    files "demo/**.cpp"

	includedirs { "include" }
    libdirs { "bin/%{cfg.longname}/" }

	filter "system:Windows" 
		links { "jengine" }
	filter "system:linux"
		links {"jengine", "Jam-Engine", "X11", "dl", "Xrandr", "Xxf86vm", "Xinerama", "Xcursor", "pthread"}
    filter {}

    filter {}