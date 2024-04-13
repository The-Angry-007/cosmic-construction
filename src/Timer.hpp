#pragma once
class Timer
{
public:
	int index;
	std::vector<std::vector<int>> updateTimes;
	std::vector<std::vector<int>> renderTimes;
	std::vector<std::string> updateNames;
	std::vector<std::string> renderNames;
	std::vector<std::string> activeTimers;
	bool isUpdate;
	bool timing;
	int getIndex(std::string name, bool isUpdate);
	void StartTiming();
	void EndTiming();
	void TimeFunc(std::string name, bool isUpdate);
	void end();
	void WriteTimes(std::ofstream& file, std::vector<std::string> names, std::vector<std::vector<int>> times);
	int nFrames;
	std::vector<sf::Clock> timers;
	void SortTimes(std::vector<std::string>& names, std::vector<std::vector<int>>& times);
	std::string MicroToMs(int micro);
	Timer();
};