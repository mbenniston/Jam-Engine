#pragma once

#include <string>
#include <vector>

struct PHYSFS_File;

using byte_t = char;

class File
{
private:
	PHYSFS_File* m_fileHandle;
	std::string m_name;
	std::vector<byte_t> m_data;

public:
	
	const std::vector<byte_t>& getData() const {
		return m_data;
	}

	File(const std::string& name, PHYSFS_File* fileHandle);
	~File() {}
};

class Archive
{
private:
	std::string m_name;

public:
		
	File readFile(const std::string& fileName);

	Archive(const std::string& name);

};

class AssetLoader final
{
private:

public:
	
	static void init(const char* argv0);
	static void deinit();

	static Archive LoadArchive(const std::string& name, const std::string& path);

	~AssetLoader();
};

