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
	Structure();
	virtual void Update(float dt);
	virtual void Render();
	void SetID(int id);
};

extern int CurrentStructureID;