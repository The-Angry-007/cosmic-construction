#pragma once
class Panel
{
public:
	Panel(sf::Vector2f pos, sf::Vector2f size, sf::Color col);
	Panel(sf::FloatRect bounds, sf::Color col);
	void Render();
	bool MouseOver();

private:
	sf::RectangleShape panel;
	sf::Color col;
	sf::FloatRect bounds;
};