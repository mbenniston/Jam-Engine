#include "jampch.h"
#include "AssetLoader.h"
#include <physfs.h>
#include <array>
#include <iostream>
#include <fstream>

#include "misc.hpp"

#include "../Gen/default_res.hpp"

namespace Jam
{
	Archive DEFAULT_ASSETS;

	void AssetLoader::init(const char* argv0)
	{
		PHYSFS_init(argv0);
		MISC_LINC();

		DEFAULT_ASSETS = LoadArchiveFromMemory(DEFAULT_RES_SRC, DEFAULT_RES_SRCLength, "default_res", "default_res.tar.gz");
	}

	void AssetLoader::deinit()
	{
		PHYSFS_deinit();
		MISC_LDEC();
	}

	Archive AssetLoader::LoadArchive(const std::string& name, const std::string& path)
	{
		int res = PHYSFS_mount(path.c_str(), name.c_str(), true);
		if (!res) {
			PLOG_INFO("{}", PHYSFS_getLastErrorCode());
			throw std::runtime_error("Could not mount archive");
		}

		return Archive(name);
	}

	Archive AssetLoader::LoadArchiveFromMemory(void* buf, size_t len, const std::string& name, const std::string& path)
	{
		int res = PHYSFS_mountMemory(buf, len, NULL, path.c_str(), name.c_str(), true);
		if (!res) {
			PLOG_INFO("PHYSFS ERROR CODE: {}", PHYSFS_getLastErrorCode());
			throw std::runtime_error("Could not mount memory archive");
		}

		return Archive(name);
	}

	AssetLoader::~AssetLoader()
	{
	}

	ArchiveFile Archive::openFile(const std::string& fileName)
	{
		PHYSFS_File* fileHandle = PHYSFS_openRead((m_name + "/" + fileName).c_str());
		if (!fileHandle) {
			throw std::runtime_error("Could not find file");
		}
		MISC_LINC();

		return ArchiveFile(fileName, fileHandle);
	}

	Archive::Archive(const std::string& name) : m_name(name)
	{
	}

	Archive::Archive() : m_name("")
	{
	}

	void ArchiveFile::close()
	{
		if (!PHYSFS_close(m_fileHandle)) {
			throw std::runtime_error("Cannot close file");
		}
		MISC_LDEC();
		m_fileHandle = nullptr;
	}

	File::File(const std::string& filePath) : m_name(filePath)
	{
		std::ifstream str(filePath, std::ios::binary | std::ios::ate | std::ios::in);

		if (!str) {
			throw std::runtime_error("Could not open file!");
		}

		std::streamsize size = str.tellg();
		str.seekg(0, std::ios::beg);

		m_data.resize(size);
		if (!str.read((char*)m_data.data(), size)) {
			throw std::runtime_error("Could not read file!");
		}
	}

	ArchiveFile::ArchiveFile(const std::string& name, PHYSFS_File* fileHandle) : m_name(name), m_fileHandle(fileHandle)
	{
		const int BUF_LEN = 100;
		std::array<byte_t, BUF_LEN> buffer;
		PHYSFS_sint64 bytesRead = 1;
		while (bytesRead > 0) {
			bytesRead = PHYSFS_readBytes(fileHandle, buffer.data(), BUF_LEN);
			m_data.insert(m_data.end(), buffer.begin(), buffer.begin() + bytesRead);
		}
	}

	ArchiveFile::~ArchiveFile()
	{
		if (m_fileHandle) {
			close();
		}
	}
}
