#include "SaveHandler.hpp"
#include <iostream>
#include <sys/stat.h>
#include <windows.h>
namespace SaveHandler
{
std::string workingDir = "";
}

void SaveHandler::CreateSave(std::string name)
{}
void SaveHandler::LoadGame(std::string name)
{}
bool SaveHandler::DirExists(std::string path)
{
	struct stat info;
	if (stat(path.c_str(), &info) != 0)
		return false;
	return (info.st_mode & S_IFDIR) != 0;
}
bool SaveHandler::CreateDirectory(std::string path)
{
	return (CreateDirectoryA(path.c_str(), NULL));
}

void SaveHandler::UpdateTimePlayed()
{}
std::string SaveHandler::ReadData(std::string path)
{
	return "";
}
void SaveHandler::WriteData(std::string path, std::string string)
{
}
std::vector<std::string> SaveHandler::ListDirectories(std::string path)
{
	WIN32_FIND_DATAA findFileData;
	HANDLE hfind = FindFirstFileA((path + "\\*").c_str(), &findFileData);
	if (hfind == INVALID_HANDLE_VALUE)
	{
		std::cerr << "Failed to list directories in: " << path << std::endl;
	}
	std::vector<std::string> dirs;
	do
	{
		if (findFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
		{
			std::string directoryName = findFileData.cFileName;
			//skip . and .. entries
			if (directoryName != "." && directoryName != "..")
			{
				dirs.push_back(directoryName);
			}
		}
	} while (FindNextFileA(hfind, &findFileData) != 0);
	FindClose(hfind);
	return dirs;
}
std::vector<std::string> SaveHandler::ListFiles(std::string path)
{
	std::vector<std::string> files;
	WIN32_FIND_DATAA fileData;
	HANDLE hFind = FindFirstFileA((path + "\\*").c_str(), &fileData); // Find the first file in the directory.

	if (hFind != INVALID_HANDLE_VALUE)
	{
		do
		{
			if (!(fileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
			{
				files.push_back(path + "\\" + fileData.cFileName); // Add the file path to the vector
			}
		} while (FindNextFileA(hFind, &fileData) != 0); // Find the next file

		FindClose(hFind); // Close the handle
	}
	else
	{
		std::cerr << "Error opening directory" << std::endl;
	}

	return files;
}
std::string SaveHandler::RelToAbsolute(std::string path)
{
	return "";
}

std::string SaveHandler::JSONsToString(std::vector<JSON> jsons)
{
	std::string s = "";
	for (uint i = 0; i < jsons.size(); i++)
	{
		s += jsons[i].ToString();
		if (i != jsons.size() - 1)
		{
			s += "\n";
		}
	}
	return s;
}

std::vector<JSON> SaveHandler::StringToJSONs(std::string string)
{
	std::vector<JSON> jsons = {};
	for (uint i = 0; i < string.size(); i++)
	{
		std::string current = "";
		while (string[i] != '}')
		{
			current += string[i];
			i++;
		}
		current += string[i];
		JSON j = JSON();
		j.FromString(current);
		jsons.push_back(j);
		current = "";
		i++;
	}
	return jsons;
}