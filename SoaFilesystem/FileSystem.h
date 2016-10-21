#pragma once
#ifndef _FILESYSTEM_H_
#define _FILESYSTEM_H_

#include <iostream>
#include <fstream>

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

	int SystemPrompt();
	void CreateFile(const std::string& file);
	void DeleteFile(const std::string& file);

};

// sizeof(FileDesc) == 64
struct FileDesc
{
	long offset;
	char name[56];
};

struct FileSystemHeader
{
	FileDesc files[128];
};

#endif // _FILESYSTEM_H_
