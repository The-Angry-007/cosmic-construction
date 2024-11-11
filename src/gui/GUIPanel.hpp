#pragma once
#include "GUIObject.hpp"
class GUIPanel : public GUIObject
{
public:
	sf::Color color;
	sf::RectangleShape rect;

	void SetColor(sf::Color color);
	void Render();
	GUIPanel(sf::Vector2f position, sf::Vector2f size, sf::Color color);
	~GUIPanel();
};