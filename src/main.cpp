#include <iostream>
#include "AssetLoader.h"
#include "PowerLogger.hpp"

#include <AL/al.h>
#include <AL/alc.h>
#include <AL/alext.h>

int main(int argc, char** argv)
{
	ALCdevice* device;
	ALCcontext* context;
	device = alcOpenDevice(NULL);
	if (!device) throw std::exception("Could not open the default device");
	
	context = alcCreateContext(device, NULL);
	if (!context) {
		throw std::exception("Could not create context");
	}
	alcMakeContextCurrent(context);

	AssetLoader::init(argv[0]);
	{
		auto a = AssetLoader::LoadArchive("myArchive", "test.zip");
		auto f = a.openFile("test.txt");
		std::cout << std::string(f.getData().begin(), f.getData().end()) << std::endl;

		std::cin.get();
	}
	AssetLoader::deinit();

	return 0;
}