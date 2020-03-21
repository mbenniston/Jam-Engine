workspace "Game Engine"
	language "C++"
	architecture "x86_64"
	configurations { "Debug", "Release" }
	cppdialect 'C++17' 

	filter { "configurations:Debug" }
        runtime "Debug"
        symbols "On"
	
	filter { "configurations:Release" }
        runtime "Release"
        optimize "On"
	filter { }
	
	targetdir ("bin/%{cfg.longname}")
    objdir ("obj/%{cfg.longname}")
    
project "Jam-Engine"
	kind "ConsoleApp"
	
	files "src/**"

	includedirs { "./modules/physfs/src/", "./modules/fmt/include/", "./modules/rlutil/" }
	
	libdirs { "deps/physfs/%{cfg.longname}/", "deps/fmt/%{cfg.longname}/" }
	
	links { "physfs-static.lib" }

	filter { "configurations:Debug" }
		links { "fmtd.lib" }
	
	filter { "configurations:Release" }
		links { "fmt.lib" }
	
	filter { }


    filter {}