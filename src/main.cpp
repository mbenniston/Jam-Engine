#include <iostream>
#include "AssetLoader.h"
#include "PowerLogger.hpp"
#include <cassert>
#include <fstream>

#include "Window.hpp"
#include "Audio.h"

int main(int argc, char** argv)
{
	InitAudio();

	Jam::Window win;
	win.open(1280, 720, "Hello window");

	Jam::AssetLoader::init(argv[0]);
	{
		auto a = Jam::AssetLoader::LoadArchive("myArchive", "test.zip");
		auto f = a.openFile("test.txt");
		std::cout << std::string(f.getData().begin(), f.getData().end()) << std::endl;

		Buffer buf;
		buf.load(Jam::File("file1.wav"));
		Source s;
		s.gen();
		s.setBuffer(buf);
		s.play();

		while (s.isPlaying() && !win.shouldClose()) {
			win.update();
		}

		buf.remove();
		s.remove();
	}
	Jam::AssetLoader::deinit();
	DeinitAudio();
	return 0;
}