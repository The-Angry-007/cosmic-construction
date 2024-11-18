#include "SaveHandler.hpp"

namespace SaveHandler
{
std::string workingDir = "";
}

void CreateSave(std::string name)
{}
void LoadGame(std::string name)
{}
bool DirExists(std::string path)
{
	return false;
}
void CreateDirectory(std::string path)
{}

void UpdateTimePlayed()
{}
std::string ReadData(std::string path)
{
	return "";
}
void WriteData(std::string path, std::string string)
{
}
std::vector<std::string> ListDirectories(std::string path)
{
	return {};
}
std::string RelToAbsolute(std::string path)
{
	return "";
}
