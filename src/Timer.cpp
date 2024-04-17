#include "Timer.hpp"
#include "SaveHandler.hpp"
#include <cstdio>
#include <fstream>
#include <iostream>
Timer::Timer()
{
	timing = false;
	nFrames = 0;
	index = 0;
	std::string path = SaveHandler::relToAbsolute("timings");

	if (!SaveHandler::dirExists(path))
	{
		SaveHandler::createDir(path);
	}
	std::vector<std::string> files = SaveHandler::listFiles(path);
	for (uint i = 0; i < files.size(); i++)
	{
		// const char* filePath = (path + "\\" + files[i] + ".txt").data();
		remove(files[i].data());
	}
}
void Timer::StartTiming()
{
	index++;
	updateTimes = {};
	renderTimes = {};
	updateNames = {};
	renderNames = {};
	nFrames = 0;
	timing = true;
}
void Timer::end()
{
	std::string name = cName;
	if (!timing)
	{
		return;
	}
	int time = timer.getElapsedTime().asMicroseconds();
	int i = getIndex(name, isUpdate);
	if (i == -1)
	{
		if (isUpdate)
		{
			updateNames.push_back(name);
			updateTimes.push_back(std::vector<int> {});
			i = updateTimes.size() - 1;
		}
		else
		{
			renderNames.push_back(name);
			renderTimes.push_back(std::vector<int> {});
			i = renderTimes.size() - 1;
		}
	}
	if (isUpdate)
	{
		updateTimes[i].push_back(time);
	}
	else
	{
		renderTimes[i].push_back(time);
	}
}
void Timer::TimeFunc(std::string name, bool isUpdate)
{
	timer.restart();
	cName = name;
	this->isUpdate = isUpdate;
}
void Timer::EndTiming()
{
	timing = false;
	std::ofstream file;
	file.open("timings\\" + std::to_string(index) + ".txt");
	file << "Update:\n";
	WriteTimes(file, updateNames, updateTimes);
	file << "Render:\n";
	WriteTimes(file, renderNames, renderTimes);
	file.close();
}
int Timer::getIndex(std::string name, bool isUpdate)
{
	if (isUpdate)
	{
		for (uint i = 0; i < updateNames.size(); i++)
		{
			if (updateNames[i] == name)
			{
				return i;
			}
		}
	}
	else
	{
		for (uint i = 0; i < renderNames.size(); i++)
		{
			if (renderNames[i] == name)
			{
				return i;
			}
		}
	}
	return -1;
}
void Timer::WriteTimes(std::ofstream& file, std::vector<std::string> names, std::vector<std::vector<int>> times)
{
	for (uint i = 0; i < names.size(); i++)
	{
		file << names[i] + ":";
		int total = 0;
		int max = 0;
		int min = 100000;
		for (uint j = 0; j < times[i].size(); j++)
		{
			total += times[i][j];
			if (times[i][j] > max)
			{
				max = times[i][j];
			}
			if (times[i][j] < min)
			{
				min = times[i][j];
			}
		}
		int avg = total / nFrames;
		file << " avg: " << avg << " max: " << max << " min: " << min << "\n";
	}
}
