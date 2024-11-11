#pragma once
#include "GUIObject.hpp"
class GUILabel : public GUIObject
{
public:
	sf::Font font;
	std::string value;
	sf::Color color;
	sf::Vector2f origin;
	sf::Text text;

	GUILabel(sf::Vector2f position, sf::Vector2f size, std::string text);
	void SetColor(sf::Color color);
	void Render();
};