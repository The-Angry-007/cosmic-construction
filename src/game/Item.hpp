#pragma once
//how big an item is in pixels
#define ITEM_SIZE 16
#include "Hitboxes.hpp"
#include "ResourceHandler.hpp"
class Planet;
class Item
{
public:
	sf::Vector2f position;
	int typeId;
	int id;
	int chunkID;
	sf::Sprite sprite;
	Hitbox* hitbox;
	Hitbox* accurateHitbox;
	int parent;
	int zindex;

	Item(sf::Vector2f position, int id, int typeID);
	void SetParent(int index);
	void Update(float dt);
	void Render(Planet* planet);
	sf::Vector2i GetTilePos();
};
extern int CurrentItemID;