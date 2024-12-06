#pragma once
//how big an item is in pixels
#define ITEM_SIZE 16.f
#include "Hitboxes.hpp"
#include "ResourceHandler.hpp"
class Item
{
public:
	sf::Vector2f position;
	int typeId;
	sf::Sprite sprite;
	Hitbox* hitbox;
	Hitbox* accurateHitbox;
	bool selected;

	Item(sf::Vector2f position);
	void Update(float dt);
	void Render();
};