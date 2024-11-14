#pragma once
#include "GUILabel.hpp"
#include "GUIObject.hpp"

class GUIInputField : public GUIObject
{
public:
	std::string value;
	std::string displayValue;
	bool changed;
	int cursorPos;
	bool focused;
	GUILabel* label;

	void SetTextCol(sf::Color color);
	GUIInputField(sf::Vector2f position, sf::Vector2f size);
	~GUIInputField();
	void Update(float dt);
	void Render();
};