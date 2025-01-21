#include "JSON.hpp"
#include "utils.hpp"

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
	std::cout << "could not find " << keyword << std::endl;
	return "not in list";
}

void JSON::AddAttribute(std::string keyword, std::string value)
{
	keywords.push_back(keyword);
	values.push_back(value);
}
void JSON::AddAttribute(std::string keyword, int value)
{
	keywords.push_back(keyword);
	values.push_back(std::to_string(value));
}
void JSON::AddAttribute(std::string keyword, float value)
{
	keywords.push_back(keyword);
	values.push_back(std::to_string(value));
}
void JSON::AddAttribute(std::string keyword, sf::Vector2f value)
{
	AddAttribute(keyword + "X", value.x);
	AddAttribute(keyword + "Y", value.y);
}
void JSON::AddAttribute(std::string keyword, sf::Vector2i value)
{
	AddAttribute(keyword + "X", value.x);
	AddAttribute(keyword + "Y", value.y);
}
int JSON::GetInt(std::string keyword)
{
	return std::stoi(GetValue(keyword));
}
float JSON::GetFloat(std::string keyword)
{
	return std::stof(GetValue(keyword));
}
sf::Vector2f JSON::GetV2f(std::string keyword)
{
	return sf::Vector2f(
		GetFloat(keyword + "X"),
		GetFloat(keyword + "Y"));
}
sf::Vector2i JSON::GetV2i(std::string keyword)
{
	return sf::Vector2i(
		GetInt(keyword + "X"),
		GetInt(keyword + "Y"));
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

std::string JSON::ToString()
{
	std::string s = "{\n";
	for (uint i = 0; i < keywords.size(); i++)
	{
		s += keywords[i] + ":" + values[i] + "\n";
	}
	s += "}";
	return s;
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

std::vector<int> JSON::GetIntArr(std::string keyword)
{
	std::string val = GetValue(keyword);
	if (val.size() == 0)
	{
		return {};
	}
	std::vector<std::string> vals = Split(val, ',');
	std::vector<int> intVals = {};
	for (int i = 0; i < vals.size(); i++)
	{
		intVals.push_back(std::stoi(vals[i]));
	}
	return intVals;
}

std::vector<float> JSON::GetFloatArr(std::string keyword)
{
	std::string val = GetValue(keyword);
	if (val.size() == 0)
	{
		return {};
	}
	std::vector<std::string> vals = Split(val, ',');
	std::vector<float> floatVals = {};
	for (int i = 0; i < vals.size(); i++)
	{
		floatVals.push_back(std::stof(vals[i]));
	}
	return floatVals;
}

std::vector<bool> JSON::GetBoolArr(std::string keyword)
{
	std::string val = GetValue(keyword);
	if (val.size() == 0)
	{
		return {};
	}
	std::vector<std::string> vals = Split(val, ',');
	std::vector<bool> boolVals = {};
	for (int i = 0; i < vals.size(); i++)
	{
		boolVals.push_back(std::stoi(vals[i]));
	}
	return boolVals;
}
