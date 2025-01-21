#pragma once

class JSON
{
public:
	std::vector<std::string> keywords;
	std::vector<std::string> values;

	JSON();
	std::string GetValue(std::string keyword);
	void AddAttribute(std::string keyword, int value);
	void AddAttribute(std::string keyword, float value);
	void AddAttribute(std::string keyword, sf::Vector2f value);
	void AddAttribute(std::string keyword, sf::Vector2i value);
	int GetInt(std::string keyword);
	float GetFloat(std::string keyword);
	sf::Vector2f GetV2f(std::string keyword);
	sf::Vector2i GetV2i(std::string keyword);
	std::vector<int> GetIntArr(std::string keyword);
	std::vector<float> GetFloatArr(std::string keyword);
	std::vector<bool> GetBoolArr(std::string keyword);
	void AddAttribute(std::string keyword, std::string value);

	/*
	this is changed slightly from design:
	in design, there was one algorithm to convert a single string
	into a list of jsons. however, i decided that in my code,
	each json will be processed individually.
	*/
	void FromString(std::string data);
	std::string ToString();

	void Print();
};