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
	bool altCharSize;

	GUILabel(sf::Vector2f position, sf::Vector2f size, std::string text);
	void SetColor(sf::Color color);
	void Render();
	void RenderToTexture(sf::RenderTexture* texture);
	void DoWrapping(int charsPerLine);
};