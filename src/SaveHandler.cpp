#include "Include.hpp"
#include <cerrno>
#include <chrono>
#include <fstream>
#include <iostream>
#include <sys/stat.h>
#include <windows.h>
std::string SaveHandler::workingDir = "";
//incremented every time the save system is changed, so outdated saves cannot be used
int SaveHandler::saveVersion = 1;
void SaveHandler::CreateSave(std::string name)
{
	ResetDir();
	if (name == "")
	{
		name = "unnamed";
	}
	int index = 0;
	std::string path;
	while (true)
	{

		path = workingDir + "\\" + name;
		if (index != 0)
		{
			path += (" " + std::to_string(index));
		}
		if (!dirExists(path))
		{
			break;
		}
		else
		{
			index++;
		}
	}
	workingDir = path;
	createDir(path);
	//finds the date of creation and sets the the time last modified to now
	std::string metadat = "";
	int64_t seconds = getSeconds();
	auto secondsString = std::to_string(seconds);
	//converts this into a date
	std::chrono::seconds sec(seconds);
	std::chrono::time_point<std::chrono::system_clock> tp(sec);
	// Convert to time_t for use with std::put_time
	std::time_t time = std::chrono::system_clock::to_time_t(tp);
	std::stringstream ss;
	ss << std::put_time(std::localtime(&time), "%d-%m-%Y");
	std::string date = ss.str();

	//now that the seconds since 1970 and the date have been obtained, they can be written to the metadata file.
	//also, set the time played to 0 seconds
	std::ofstream fs(workingDir + "\\metadata.txt");
	fs << date << std::endl
	   << seconds << std::endl
	   << "0" << std::endl
	   << (std::to_string(saveVersion));
	fs.close();
}

//c++ black magic fuckery
bool SaveHandler::dirExists(std::string& path)
{
	struct stat info;
	if (stat(path.c_str(), &info) != 0)
		return false;
	return (info.st_mode & S_IFDIR) != 0;
}
bool SaveHandler::createDir(std::string& path)
{
	return (CreateDirectoryA(path.c_str(), NULL));
}

void SaveHandler::UpdateModified()
{
	std::string path = workingDir + "\\metadata.txt";
	auto lines = getLines(path);
	lines[1] = std::to_string(getSeconds());
	WriteLines(lines, path);
}
void SaveHandler::UpdateTimePlayed(int seconds)
{
	std::string path = workingDir + "\\metadata.txt";
	auto lines = getLines(path);
	int played = std::stoi(lines[2]);
	played += seconds;
	auto pstring = std::to_string(played);
	lines[2] = pstring;
	WriteLines(lines, path);
}
std::vector<std::string> SaveHandler::getLines(std::string path)
{
	std::string line;
	std::vector<std::string> lines;
	std::ifstream file(path);
	while (getline(file, line))
	{
		lines.push_back(line);
	}
	file.close();
	return lines;
}
void SaveHandler::WriteLines(std::vector<std::string> lines, std::string path)
{
	std::ofstream file(path);
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
int64_t SaveHandler::getSeconds()
{
	auto now = std::chrono::system_clock::now();
	return std::chrono::duration_cast<std::chrono::seconds>(now.time_since_epoch()).count();
}
std::vector<std::string> SaveHandler::listFiles(std::string& directory)
{
	std::vector<std::string> files;
	WIN32_FIND_DATAA fileData;
	HANDLE hFind = FindFirstFileA((directory + "\\*").c_str(), &fileData); // Find the first file in the directory.

	if (hFind != INVALID_HANDLE_VALUE)
	{
		do
		{
			if (!(fileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
			{
				files.push_back(directory + "\\" + fileData.cFileName); // Add the file path to the vector
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
std::vector<std::string> SaveHandler::listDirs(std::string& path)
{

	WIN32_FIND_DATAA findFileData;
	HANDLE hFind = FindFirstFileA((path + "\\*").c_str(), &findFileData);

	if (hFind == INVALID_HANDLE_VALUE)
	{
		std::cerr << "Failed to list directories in: " << path << std::endl;
		return {};
	}
	std::vector<std::string> dirs;
	do
	{
		if (findFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
		{
			std::string directoryName = findFileData.cFileName;
			// Skip "." and ".." entries
			if (directoryName != "." && directoryName != "..")
			{
				dirs.push_back(directoryName);
			}
		}
	} while (FindNextFileA(hFind, &findFileData) != 0);

	FindClose(hFind);
	return dirs;
}

void SaveHandler::ResetDir()
{
	std::string appdata = getenv("APPDATA");
	workingDir = appdata + "\\cosmic-construction";
	if (!dirExists(workingDir))
	{
		createDir(workingDir);
	}
	workingDir += "\\saves";
	if (!dirExists(workingDir))
	{

		createDir(workingDir);
	}
}

void SaveHandler::SaveGame()
{
	//update metadata
	std::vector<std::string> metadata = getLines(workingDir + "\\metadata.txt");
	std::cout << metadata.size() << std::endl;
	int seconds = std::stoi(metadata[2]);
	seconds += game->timePassed->getElapsedTime().asSeconds();
	metadata[2] = std::to_string(seconds);
	WriteLines(metadata, workingDir + "\\metadata.txt");
	std::vector<std::string> items;
	for (uint i = 0; i < game->items.size(); i++)
	{
		items.push_back(game->items[i].toString());
	}
	WriteLines(items, workingDir + "\\items.txt");
}

void SaveHandler::LoadGame()
{
	std::vector<std::string> items = getLines(workingDir + "\\items.txt");
	for (uint i = 0; i < items.size(); i++)
	{
		game->items.push_back(Item(items[i]));
	}
}

std::string SaveHandler::relToAbsolute(std::string relativePath)
{
	char fullPath[MAX_PATH];
	if (GetFullPathNameA(relativePath.c_str(), MAX_PATH, fullPath, NULL))
	{
		return std::string(fullPath);
	}
	return ""; // Return an empty string if conversion fails
}