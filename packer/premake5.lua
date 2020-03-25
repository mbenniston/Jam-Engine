workspace "Res-Packer"
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
		defines { "NDEBUG" }
	filter { }
	
	targetdir (".")
    objdir (".")

    
project "packer"
	kind "ConsoleApp"

	files "packer.cpp"
	
    filter {}