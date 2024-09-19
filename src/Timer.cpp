#include "Include.hpp"
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
	if (!timing)
	{
		return;
	}
	std::string name = activeTimers[activeTimers.size() - 1];
	activeTimers.erase(activeTimers.end() - 1);

	int time = timers[timers.size() - 1].getElapsedTime().asMicroseconds();
	timers.erase(timers.end() - 1);
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
	activeTimers.push_back(name);
	timers.push_back(sf::Clock());
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
	std::vector<std::vector<int>> processed;
	for (uint i = 0; i < names.size(); i++)
	{
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
		processed.push_back(std::vector<int> { min, max, avg });
		//file << " avg: " << avg << " max: " << max << " min: " << min << "\n";
	}
	SortTimes(names, processed);
	for (uint i = 0; i < names.size(); i++)
	{
		file << names[i] + ": avg: ";
		file << MicroToMs(processed[i][2]);
		file << " min: ";
		file << MicroToMs(processed[i][0]);
		file << " max: ";
		file << MicroToMs(processed[i][1]) << "\n";
	}
}

void Timer::SortTimes(std::vector<std::string>& names, std::vector<std::vector<int>>& times)
{
	//basic bubble sort algorithm
	for (uint i = 0; i < names.size(); i++)
	{
		bool flag = false;
		for (uint j = 0; j < names.size() - i - 1; j++)
		{
			if (times[j + 1][2] > times[j][2])
			{
				flag = true;
				std::vector<int> temp = times[j + 1];
				times[j + 1] = times[j];
				times[j] = temp;
				std::string temp2 = names[j + 1];
				names[j + 1] = names[j];
				names[j] = temp2;
			}
		}
	}
}

std::string Timer::MicroToMs(int micro)
{
	float ms = micro / 1000.f;
	std::ostringstream stream;
	stream << std::fixed << std::setprecision(1) << ms << "ms";
	return stream.str();
}