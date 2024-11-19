#pragma once
#include "JSON.hpp"

namespace SaveHandler
{
extern std::string workingDir;

void CreateSave(std::string name);
void LoadGame(std::string name);
bool DirExists(std::string path);
bool CreateDirectory(std::string path);
void UpdateTimePlayed();
std::string ReadData(std::string path);
void WriteData(std::string path, std::string string);
std::vector<std::string> ListFiles(std::string path);
std::vector<std::string> ListDirectories(std::string path);
std::string RelToAbsolute(std::string path);

std::string JSONsToString(std::vector<JSON> jsons);
std::vector<JSON> StringToJSONs(std::string string);
}