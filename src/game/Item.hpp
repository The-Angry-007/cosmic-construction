#pragma once
//how big an item is in pixels
#define ITEM_SIZE 16.f
class Item
{
public:
	sf::Vector2f position;
	Item(sf::Vector2f position);
	void Update(float dt);
	void Render();
};