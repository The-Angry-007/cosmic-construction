#pragma once
//how big an item is in pixels
#define ITEM_SIZE 16
#include "Hitboxes.hpp"
#include "ResourceHandler.hpp"
class Item
{
public:
	sf::Vector2f position;
	int typeId;
	int id;
	sf::Sprite sprite;
	Hitbox* hitbox;
	Hitbox* accurateHitbox;
	bool selected;

	Item(sf::Vector2f position, int id, int typeID);
	void Update(float dt);
	void Render();
};
extern int CurrentItemID;