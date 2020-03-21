#include <iostream>
#include "AssetLoader.h"
#include "PowerLogger.hpp"

int main(int argc, char** argv)
{
	AssetLoader::init(argv[0]);

	auto a = AssetLoader::LoadArchive("myArchive", "test.zip");
	auto f = a.readFile("test.txt");
	std::cout << std::string(f.getData().begin(), f.getData().end()) << std::endl;

	std::cin.get();

	AssetLoader::deinit();

	return 0;
}