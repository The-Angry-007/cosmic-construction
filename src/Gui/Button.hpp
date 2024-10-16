#pragma once
#include "Gui/GuiObject.hpp"
void DefaultClickFunc();
class Button : public GuiObject
{
public:
	Button(sf::Vector2f pos, sf::Vector2f size, sf::Color col, sf::Texture image, std::function<void()> onClick = DefaultClickFunc);
	Button(sf::Vector2f pos, sf::Vector2f size, sf::Color col, std::string label, sf::Color labelCol = sf::Color::Black, std::function<void()> onClick = DefaultClickFunc);
	void Render();
	bool clicked();
	void AssignOnClick(std::function<void()> func);
	bool mouseOverButton();
	bool keepImageRatio;
	~Button();
	//sf::Vector2f pos;
	std::function<void()> onClickFunction;

	//between 0 and 1, where 0 is left of screen and 1 is right
	//sf::Vector2f size;
	sf::RectangleShape* bg;
	sf::Text textLabel;
	sf::Texture imageLabel;
	sf::Sprite imageSprite;
	bool hasImageLabel;
};
