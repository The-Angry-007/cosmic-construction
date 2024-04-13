#pragma once
class Button;
class Label;
//an input field is essentially a button with a label on, and the label
//changes as the user types
class InputField
{
public:
	InputField(sf::FloatRect bounds, sf::Color col, int maxChars = -1);
	InputField(sf::Vector2f pos, sf::Vector2f size, sf::Color col, int maxChars = -1);
	void Render();
	void Update();
	std::string text;

private:
	int maxChars;
	Button* selectButton;
	sf::FloatRect bounds;
	sf::Color bgCol;
	Label* label;
	bool selected;
	int typeSpot;
};