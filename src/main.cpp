#include "jampch.h"
#include <iostream>

#include <cassert>
#include <fstream>

#include "Graphics/Window.hpp"
#include "Audio/Audio.h"
#include "Assets/AssetLoader.h"
#include "PowerLogger.hpp"

int main(int argc, char** argv)
{
	Jam::InitAudio();
	Jam::AssetLoader::init(argv[0]);

	Jam::Window win(1280, 720, "Hello window");
	{
		auto a = Jam::AssetLoader::LoadArchive("myArchive", "test.zip");
		auto f = a.openFile("test.txt");
		std::cout << std::string(f.getData().begin(), f.getData().end()) << std::endl;

		Jam::Buffer buf;
		buf.load(Jam::File("file1.wav"));
		Jam::Source s;
		s.gen();
		s.setBuffer(buf);
		s.play();

		while (s.isPlaying() && !win.shouldClose()) {
			win.update();
		}

		win.close();
		std::cin.get();

		buf.remove();
		s.remove();
	
	}
	Jam::AssetLoader::deinit();
	Jam::DeinitAudio();
	return 0;
}