#pragma once
namespace SaveHandler
{
extern int saveVersion;
void CreateSave(std::string name);
bool SaveExists(std::string name);
bool dirExists(std::string& path);
extern std::string workingDir;
bool createDir(std::string& path);
void UpdateModified();
void UpdateTimePlayed(int seconds);
int64_t getSeconds();
std::vector<std::string> getLines(std::string path);
void WriteLines(std::vector<std::string> lines, std::string path);
std::vector<std::string> listDirs(std::string& path);
std::vector<std::string> listFiles(std::string& directory);
void ResetDir();
void SaveGame();
void LoadGame();
std::string relToAbsolute(std::string relativePath);
}