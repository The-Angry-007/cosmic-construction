#pragma once

class Table
{
public:
	std::vector<std::string> headers;
	std::vector<std::vector<std::string>> records;

	Table();
	void FromString(std::string string);
	std::string GetValue(int column, int row);
	std::string GetValue(std::string header, int row);
	std::string ToString();
};