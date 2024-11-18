#pragma once
#include "saving/JSON.hpp"
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
