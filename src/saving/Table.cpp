#include "Table.hpp"
#include "utils.hpp"
Table::Table()
{
	headers = {};
	records = {};
}

void Table::FromString(std::string string)
{
	auto lines = Split(string, '\n');
	headers = Split(lines[0], ',');
	for (uint i = 1; i < lines.size(); i++)
	{
		records.push_back(Split(lines[i], ','));
	}
}

std::string Table::GetValue(int column, int row)
{
	return records[row][column];
}

std::string Table::GetValue(std::string header, int row)
{
	for (uint i = 0; i < headers.size(); i++)
	{
		if (headers[i] == header)
		{
			return records[row][i];
		}
	}
	return "data not found";
}