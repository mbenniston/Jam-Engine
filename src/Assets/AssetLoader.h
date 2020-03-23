#pragma once

#include <string>
#include <vector>

struct PHYSFS_File;

namespace Jam
{
	using byte_t = char;

	class File
	{
	private:
		std::string m_name;

	protected:
		std::vector<byte_t> m_data;

	public:

		const std::vector<byte_t>& getData() const {
			return m_data;
		}

		File() = default;
		File(const std::string& filePath);
		virtual ~File() = default;
	};

	class ArchiveFile : public File
	{
	private:
		PHYSFS_File* m_fileHandle;
		std::string m_name;

	public:

		void close();

		ArchiveFile(const std::string& name, PHYSFS_File* fileHandle);
		~ArchiveFile();
	};

	class Archive
	{
	private:
		std::string m_name;

	public:

		ArchiveFile openFile(const std::string& fileName);

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

}