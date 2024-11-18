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

	/*
	this is changed slightly from design:
	in design, there was one algorithm to convert a single string
	into a list of jsons. however, i decided that in my code,
	each json will be processed individually.
	*/
	void FromString(std::string data);

	void Print();
};