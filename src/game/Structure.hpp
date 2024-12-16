#pragma once
#include "Hitboxes.hpp"
#include "saving.hpp"
class Structure
{
public:
	int typeID;
	int id;
	int chunkID;
	int planetID;
	int zindex;
	sf::Vector2i bottomRightPos;
	sf::Vector2i position;
	sf::Vector2i tileSize;
	sf::Sprite sprite;
	Hitbox* hitbox;
	Structure();
	virtual void Update(float dt);
	virtual void Render();
	void SetPosition(sf::Vector2i position);
	void SetID(int id);
	virtual JSON ToJSON();
	virtual void FromJSON();
};

extern int CurrentStructureID;