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
	sf::Vector2f moveDir;
	Hitbox* hitbox;
	Hitbox* accurateHitbox;
	int parent;
	int zindex;
	bool isDeleted = false;

	Item(sf::Vector2f position, int id, int typeID);
	//specifically for creating one that is deleted
	Item();
	void SetType(int typeID);
	void SetParent(int index);
	void Update(float dt, Planet* planet);
	void Render(Planet* planet);
	sf::Vector2i GetTilePos();
};
extern int CurrentItemID;