#include "SaveHandler.hpp"
#include "Main.hpp"
#include "game/RandomHandler.hpp"
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
sf::Clock saveTimer;
}

void SaveHandler::ResetWorkingDir()
{
	std::string appdata = getenv("APPDATA");
	workingDir = appdata + "\\cosmic-construction";
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

void SaveHandler::CreateSave(std::string name, int difficulty, std::string seed)
{
	uint64_t hashedSeed = HashFromString(seed);
	RandomHandler::SetSeed(hashedSeed);
	hashedSeed = RandomHandler::GetNextNumber();
	RandomHandler::SetSeed(hashedSeed);
	//folders are named numbers instead of the actual name
	//this allows for illegal characters etc in the name

	//get the number to be used for the folder
	//this will be one more than the number of existing saves
	auto existingSaves = ListDirectories(workingDir + "\\saves");
	int highest = 0;
	for (uint i = 0; i < existingSaves.size(); i++)
	{
		std::string name = existingSaves[i];
		int index = std::stoi(name);
		if (index > highest)
		{
			highest = index;
		}
	}
	std::string fileName = std::to_string(highest + 1);
	ResetWorkingDir();
	workingDir += "\\saves\\" + fileName;
	CreateDirectory(workingDir);
	//the 2 zeroes are to set default values for
	//time played and last modified
	std::string metadata = name + "\n0\n0\n" + std::to_string(difficulty) + "\n" + std::to_string(hashedSeed);
	WriteData(workingDir + "\\metadata.txt", metadata);
	startTime = GetTime();
	UpdateTimePlayed();
	UpdateLastModified();
	game = new Game();
	game->NewGame();
}
void SaveHandler::LoadGame(int index)
{
	startTime = GetTime();
	workingDir += "\\saves\\" + std::to_string(index);
	auto metadata = Split(ReadData(workingDir + "\\metadata.txt"), '\n');
	uint64_t seed = std::stoull(metadata[4]);
	RandomHandler::SetSeed(seed);
	game = new Game();
	game->LoadGame();
}
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
	startTime = currentTime;
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

void SaveHandler::SaveGame()
{
	UpdateTimePlayed();
	UpdateLastModified();
	for (uint i = 0; i < game->planets.size(); i++)
	{
		game->planets[i].Save();
	}
}

bool SaveHandler::DeleteDirectory(std::string& path)
{
	WIN32_FIND_DATAA findFileData;
	HANDLE hFind = INVALID_HANDLE_VALUE;
	std::string searchPath = path + "\\*";
	hFind = FindFirstFileA(searchPath.c_str(), &findFileData);

	if (hFind == INVALID_HANDLE_VALUE)
	{
		return false;
	}
	do
	{
		std::string itemName = findFileData.cFileName;
		if (itemName == "." || itemName == "..")
		{
			continue;
		}
		std::string fullPath = path + "\\" + itemName;
		if (findFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
		{
			if (!DeleteDirectory(fullPath))
			{
				FindClose(hFind);
				return false;
			}
		}
		else
		{
			if (DeleteFileA(fullPath.c_str()) == 0)
			{
				FindClose(hFind);
				return false;
			}
		}
	} while (FindNextFileA(hFind, &findFileData) != 0);
	FindClose(hFind);
	if (RemoveDirectoryA(path.c_str()) == 0)
	{
		return false;
	}
	return true;
}
//FNV-1a algorithm
uint64_t SaveHandler::HashFromString(std::string& str)
{
	// Constants for FNV-1a
	const uint64_t FNV_OFFSET_BASIS = 14695981039346656037ULL;
	const uint64_t FNV_PRIME = 1099511628211ULL;

	uint64_t hash = FNV_OFFSET_BASIS;
	for (char c : str)
	{
		hash ^= static_cast<uint64_t>(c);
		hash *= FNV_PRIME;
	}
	return hash;
}