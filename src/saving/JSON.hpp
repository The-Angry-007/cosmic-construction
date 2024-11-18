#pragma once

class JSON
{
public:
	std::vector<std::string> keywords;
	std::vector<std::string> values;

	JSON();
	std::string GetValue(std::string keyword);
	void AddAttribute(std::string keyword, std::string value);
	std::string ToString();
};