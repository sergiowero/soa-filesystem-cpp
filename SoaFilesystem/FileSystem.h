#pragma once
#ifndef _FILESYSTEM_H_
#define _FILESYSTEM_H_

#include <iostream>
#include <fstream>

// sizeof(FileDesc) == 64
struct FileDesc
{
	long offset;
	char name[56];
};

union FileSystemHeader
{
	FileDesc files[128];
	char data[8192];
};

class Filesystem
{
public:
	const int FILESYSTEM_SIZE = 1024 * 1024 * 2;
	const char* FILESYSTEM_FILE_NAME = "filesystem_file";
	const int MAX_FILES = 128;

	Filesystem();
	~Filesystem();

	void CheckFileSystem();
	void Start();

private:

	std::fstream m_filesystem;
	FileSystemHeader m_header;

	int SystemPrompt();
	void CreateFile(const std::string& file);
	void DeleteFile(const std::string& file);
	void ListFiles();
	void WriteFileSystemHeader();
};



#endif // _FILESYSTEM_H_
