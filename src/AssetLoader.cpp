#include "AssetLoader.h"
#include <physfs.h>
#include <array>
#include <iostream>

void AssetLoader::init(const char* argv0)
{
	PHYSFS_init(argv0);
}

void AssetLoader::deinit()
{
	PHYSFS_deinit();
}

Archive AssetLoader::LoadArchive(const std::string& name, const std::string& path)
{
	int res = PHYSFS_mount(path.c_str(), name.c_str(), true);
	if (!res) {
		throw std::exception("Could not mount archive");
	}

	return Archive(name);
}

AssetLoader::~AssetLoader()
{
}

File Archive::readFile(const std::string& fileName)
{
	PHYSFS_File* fileHandle = PHYSFS_openRead((m_name + "/" + fileName).c_str());
	if (!fileHandle) {
		throw std::exception("Could not find file");
	}
	
	return File(fileName, fileHandle);
}

Archive::Archive(const std::string& name) : m_name(name)
{
}

File::File(const std::string& name, PHYSFS_File* fileHandle) : m_name(name), m_fileHandle(fileHandle)
{
	const int BUF_LEN = 100;
	std::array<byte_t, BUF_LEN> buffer;
	PHYSFS_sint64 bytesRead = 1;
	while (bytesRead > 0) {
		bytesRead = PHYSFS_readBytes(fileHandle, buffer.data(), BUF_LEN);
		m_data.insert(m_data.end(), buffer.begin(), buffer.begin() + bytesRead);
	}
}
