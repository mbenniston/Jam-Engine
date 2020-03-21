#include <iostream>
#include "AssetLoader.h"
#include "PowerLogger.hpp"
#include <cassert>

#include <AL/al.h>
#include <AL/alc.h>
#include <AL/alext.h>

#include <AL/alut.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

int main(int argc, char** argv)
{
	assert(glfwInit() == GLFW_TRUE);

	auto win = glfwCreateWindow(1280, 720, "Hello there", NULL, NULL);
	glfwMakeContextCurrent(win);

	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

	alutInit(&argc, argv);
	ALCdevice* device;
	ALCcontext* context;
	device = alcOpenDevice(NULL);
	if (!device) throw std::exception("Could not open the default device");
	
	context = alcCreateContext(device, NULL);
	if (!context) {
		throw std::exception("Could not create context");
	}
	alcMakeContextCurrent(context);

	ALuint buffer = alutCreateBufferHelloWorld();
	ALuint source;
	alGenSources(1, &source);
	alSourcei(source, AL_BUFFER, buffer);

	std::cout << buffer << std::endl;
	std::cout << "Playing source" << std::endl;
	alSourcePlay(source);

	AssetLoader::init(argv[0]);
	{
		auto a = AssetLoader::LoadArchive("myArchive", "test.zip");
		auto f = a.openFile("test.txt");
		std::cout << std::string(f.getData().begin(), f.getData().end()) << std::endl;

		std::cin.get();
	}
	AssetLoader::deinit();
	glfwTerminate();

	return 0;
}