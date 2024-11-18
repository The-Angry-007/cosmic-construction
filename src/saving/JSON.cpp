#include "JSON.hpp"

JSON::JSON()
{
	keywords = {};
	values = {};
}

std::string JSON::GetValue(std::string keyword)
{
	for (uint i = 0; i < keywords.size(); i++)
	{
		if (keywords[i] == keyword)
		{
			return values[i];
		}
	}
	return "not in list";
}

void JSON::AddAttribute(std::string keyword, std::string value)
{
	keywords.push_back(keyword);
	values.push_back(value);
}

void JSON::FromString(std::string data)
{
	//skip first two chars as they will always be {\n
	int index = 2;
	while (data[index] != '}')
	{
		std::string keyword = "";
		while (data[index] != ':')
		{
			keyword += data[index];
			index++;
		}
		index++;
		std::string value = "";
		while (data[index] != '\n')
		{
			value += data[index];
			index++;
		}
		AddAttribute(keyword, value);
		index++;
	}
}

void JSON::Print()
{
	std::cout << "Keywords: [";
	for (uint i = 0; i < keywords.size(); i++)
	{
		std::cout << keywords[i];
		if (i != keywords.size() - 1)
		{
			std::cout << ",";
		}
	}
	std::cout << "]\nValues: [";
	for (uint i = 0; i < values.size(); i++)
	{
		std::cout << values[i];
		if (i != values.size() - 1)
		{
			std::cout << ",";
		}
	}
	std::cout << "]";
}