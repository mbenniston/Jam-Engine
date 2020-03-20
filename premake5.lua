workspace "Game Engine"
	language "C++"
	architecture "x86_64"
	configurations { "Debug", "Release" }
	
	filter { "configurations:Debug" }
		symbols "On"
	
	filter { "configurations:Release" }
		optimize "On"
	
	filter { }
	
	targetdir ("Build/Bin/%{prj.name}/%{cfg.longname}")
	objdir ("Build/Obj/%{prj.name}/%{cfg.longname}")

project "Jam-Engine"
	kind "StaticLib"
	files "./src/**"
