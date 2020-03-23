#include "jampch.h"
#include <iostream>

#include <cassert>
#include <fstream>

#include "Graphics/Window.hpp"
#include "Audio/Audio.h"
#include "Assets/AssetLoader.h"
#include "PowerLogger.hpp"
#include "Graphics/Core/ImGuiHelper.hpp"

int main(int argc, char** argv)
{
	Jam::InitAudio();
	Jam::AssetLoader::init(argv[0]);

	Jam::Window win(1280, 720, "Hello window");
	{
		ImGuiHelper::setup(win.getHandle());
		auto a = Jam::AssetLoader::LoadArchive("myArchive", "test.zip");
		auto f = a.openFile("test.txt");
		std::cout << std::string(f.getData().begin(), f.getData().end()) << std::endl;

		Jam::Buffer buf;
		buf.load(Jam::File("file1.wav"));
		Jam::Source s;
		s.gen();
		s.setBuffer(buf);
		s.play();

		while (s.isPlaying() || !win.shouldClose()) {
			glClear(GL_COLOR_BUFFER_BIT);
			glClearColor(0, 1, 1, 1);
			ImGuiHelper::startFrame();
			ImGui::ShowDemoWindow();
			ImGuiHelper::endFrame(win.getHandle());
			win.update();
		}
		s.play();

		std::cin.get();

		buf.remove();
		s.remove();
		ImGuiHelper::cleanup();
	}
	Jam::AssetLoader::deinit();
	Jam::DeinitAudio();
	return 0;
}