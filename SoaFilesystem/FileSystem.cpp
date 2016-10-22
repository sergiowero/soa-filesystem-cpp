#include "FileSystem.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

Filesystem::Filesystem()
{
	cout << " -----------------------------------------------------------------------------" << endl;
	cout << " - File system for SOA class" << endl;
	cout << " - Version 0.0.1" << endl;
	cout << " -----------------------------------------------------------------------------" << endl;
}

Filesystem::~Filesystem()
{
	if (m_filesystem.is_open())
		m_filesystem.close();
}

void Filesystem::CheckFileSystem()
{
	ifstream is(FILESYSTEM_FILE_NAME);

	if (is.fail()) 
	{
		cout << "[INFO] File System not found " << endl;
		cout << "[INFO] Creating filesystem file ... " << endl;
		ofstream os(FILESYSTEM_FILE_NAME);
		for (int i = 0; i < FILESYSTEM_SIZE; i++)
		{
			os.put('\0');
		}
		os.close();
		cout << "[INFO] Filesystem created " << endl << endl;
	}

	is.close();
}

void Filesystem::Start()
{
	m_filesystem.open(FILESYSTEM_FILE_NAME, fstream::in | fstream::out);
	if (m_filesystem.is_open())
	{
		m_filesystem.read(m_header.data, sizeof(FileSystemHeader));
		int option = 0;
		while (option != -1)
		{
			option = SystemPrompt();
		}
	}
	m_filesystem.close();
}

int Filesystem::SystemPrompt()
{
	string command;
	string file;
	cout << ">> ";
	getline(cin, command);

	stringstream ss;

	ss << command;

	ss >> command >> file;

	if (command == "create")
	{
		CreateFile(file);
	}
	else if (command == "delete") 
	{
		DeleteFile(file);
	}
	else if (command == "ls")
	{
		ListFiles();
	}
	else if (command == "clear")
	{
		system("cls");
	}
	else if (command == "exit" || command == "quit")
	{
		return -1;
	}
	else 
	{
		cout << "Error: Command \"" << command << "\" not found" << endl;
	}
	return 0;
}

void Filesystem::CreateFile(const string& file)
{
	if (file.size() == 0) 
	{
		cout << "[ERROR] CreateFile: File name not specified" << endl << endl;
		return;
	}
	cout << "Creating file " << file << endl << endl;

	int index = 0;
	//Find index
	for (int i = 0; i < MAX_FILES; i++)
	{
		if (m_header.files[i].name[0] == '\0')
		{
			index = i;
			break;
		}
	}
	sprintf_s(m_header.files[index].name, file.size() + 1, "%s", file.c_str());

	WriteFileSystemHeader();
}

void Filesystem::DeleteFile(const string& file)
{
	if (file.size() == 0)
	{
		cout << "[ERROR] DeleteFile: File name not specified" << endl << endl;
		return;
	}
	bool found = false;
	for (int i = 0; i < MAX_FILES; i++)
	{
		if (strcmp(m_header.files[i].name, file.c_str()) == 0)
		{
			cout << "Deleting file " << file << endl << endl;
			m_header.files[i].name[0] = '\0';
			found = true;
			break;
		}
	}
	
	if (!found)
	{
		cout << "File \"" << file << "\" not found" << endl << endl;
	} 
	else
	{
		WriteFileSystemHeader();
	}
}

void Filesystem::ListFiles()
{
	for (int i = 0; i < MAX_FILES; i++)
	{
		if(m_header.files[i].name[0] != '\0')
		{
			cout << " - " << m_header.files[i].name << endl;
		}
	}

	cout << endl;
}

void Filesystem::WriteFileSystemHeader()
{
	m_filesystem.seekg(0);
	m_filesystem.write(m_header.data, sizeof(FileSystemHeader));
	m_filesystem.flush();
}