#include "SaveHandler.hpp"
#include "utils.hpp"
#include <chrono>
#include <ctime>
#include <iostream>
#include <sys/stat.h>
#include <windows.h>
namespace SaveHandler
{
std::string workingDir = "";
//the time the current save was opened
int startTime = 0;
}

void SaveHandler::Init()
{
	//reset working directory and make sure root folder exists
	std::string appdata = getenv("APPDATA");
	workingDir = appdata + "\\cosmic-construction";
	if (!DirExists(workingDir))
	{
		CreateDirectory(workingDir);
	}
	auto saveDir = workingDir + "\\saves";
	if (!DirExists(saveDir))
	{
		CreateDirectory(saveDir);
	}
}

void SaveHandler::CreateSave(std::string name)
{
	//folders are named numbers instead of the actual name
	//this allows for illegal characters etc in the name

	//get the number to be used for the folder
	//this will be one more than the number of existing saves
	auto existingSaves = ListDirectories(workingDir + "\\saves");
	std::string fileName = std::to_string(existingSaves.size() + 1);
	workingDir += "\\saves\\" + fileName;
	CreateDirectory(workingDir);
	//the 2 zeroes are to set default values for
	//time played and last modified
	std::string metadata = name + "\n0\n0";
	WriteData(workingDir + "\\metadata.txt", metadata);
	startTime = GetTime();
	UpdateTimePlayed();
	UpdateLastModified();
}
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
{
	//note that the structure of metadata will be:
	/*
	name
	time played
	last modified
	*/
	std::string path = RelToAbsolute("metadata.txt");
	std::string data = ReadData(path);
	auto lines = Split(data, '\n');
	int played = std::stoi(lines[1]);
	int currentTime = GetTime();
	played += currentTime - startTime;
	lines[1] = std::to_string(played);
	data = concat(lines);
	WriteData(path, data);
}
int SaveHandler::GetTime()
{
	auto now = std::chrono::system_clock::now();
	auto epoch = now.time_since_epoch();
	auto seconds = std::chrono::duration_cast<std::chrono::seconds>(epoch);
	return seconds.count();
}

void SaveHandler::UpdateLastModified()
{
	std::string path = RelToAbsolute("metadata.txt");
	std::string data = ReadData(path);
	auto lines = Split(data, '\n');
	int currentTime = GetTime();
	lines[2] = std::to_string(currentTime);
	data = concat(lines);
	WriteData(path, data);
}
std::string SaveHandler::ReadData(std::string path)
{
	std::string data;
	std::ifstream file(path);
	std::string line;
	while (std::getline(file, line))
	{
		data += line;
		data += '\n';
	}
	//get rid of final new line
	data = data.substr(0, data.size() - 1);
	file.close();
	return data;
}
void SaveHandler::WriteData(std::string path, std::string string)
{
	std::ofstream file(path);
	auto lines = Split(string, '\n');
	for (uint i = 0; i < lines.size(); i++)
	{
		file << lines[i];
		if (i != lines.size() - 1)
		{
			file << std::endl;
		}
	}
	file.close();
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
	return workingDir + '\\' + path;
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