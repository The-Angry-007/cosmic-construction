#include "SaveHandler.hpp"

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
	return false;
}
void SaveHandler::CreateDirectory(std::string path)
{}

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
	return {};
}
std::string SaveHandler::RelToAbsolute(std::string path)
{
	return "";
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