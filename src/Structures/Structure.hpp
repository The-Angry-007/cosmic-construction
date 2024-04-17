#pragma once
class Structure
{
public:
	//position of top left square
	sf::Vector2f pos;
	sf::Vector2i size;
	int id;
	bool animated;
	sf::Clock animTimer;
	sf::IntRect textureBounds;
	sf::Sprite* sprite;
	int dir;
};