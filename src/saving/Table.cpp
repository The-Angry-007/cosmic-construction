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
	if (row > records.size() || column > headers.size())
	{
		return "out of bounds";
	}
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

std::string Table::ToString()
{
	std::string result = "";
	for (uint i = 0; i < headers.size(); i++)
	{
		result += headers[i];
		if (i != headers.size() - 1)
		{
			result += ",";
		}
	}
	result += "\n";
	for (uint i = 0; i < records.size(); i++)
	{
		for (uint j = 0; j < records[i].size(); j++)
		{
			result += records[i][j];
			if (j != records[i].size() - 1)
			{
				result += ",";
			}
		}
		if (i != records.size() - 1)
		{
			result += "\n";
		}
	}
	return result;
}