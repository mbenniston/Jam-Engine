#include <iostream>
#include <physfs.h>

int main(int argc, char** argv)
{
	PHYSFS_init(argv[0]);
	PHYSFS_mount("res","./res/", true);
	PHYSFS_deinit();

	std::cout << "hello world" << std::endl;
	std::cin.get();
	return 0;
}