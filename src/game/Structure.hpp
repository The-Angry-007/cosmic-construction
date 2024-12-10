#pragma once
#include "Hitboxes.hpp"
class Structure
{
public:
	int typeID;
	int id;
	int chunkID;
	int planetID;
	sf::Vector2i position;
	sf::Vector2i tileSize;
	sf::Sprite sprite;
	Hitbox* hitbox;
	Structure(sf::Vector2i position, int typeID, int id, int chunkID, int planetID);
	void Update(float dt);
	void Render();
};

extern int CurrentStructureID;