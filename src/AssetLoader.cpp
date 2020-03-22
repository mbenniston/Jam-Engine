#include "AssetLoader.h"
#include <physfs.h>
#include <array>
#include <iostream>
#include <fstream>

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

File Archive::openFile(const std::string& fileName)
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

void File::close()
{
	if (m_fileHandle && !PHYSFS_close(m_fileHandle)) {
		throw std::exception("Cannot close file");
		m_fileHandle = nullptr;
	}
}

File::File(const std::string& filePath) : m_fileHandle(nullptr)
{
	std::ifstream str(filePath, std::ios::binary | std::ios::ate | std::ios::in);

	if (!str) {
		throw std::exception("Could not open file!");
	}

	std::streamsize size = str.tellg();
	str.seekg(0, std::ios::beg);

	m_data.resize(size);
	if (!str.read(m_data.data(), size)) {
		throw std::exception("Could not read file!");
	}
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

File::~File()
{
	if (m_fileHandle) {
		close();
	}
}
