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
	bool blocksItems;
	bool placedByPlayer;
	sf::Vector2i bottomRightPos;
	sf::Vector2i position;
	sf::Vector2i tileSize;
	sf::Sprite sprite;
	Hitbox* hitbox;
	Structure();
	virtual void Update(float dt);
	virtual void Render();
	virtual void SetPosition(sf::Vector2i position);
	void SetID(int id);
	virtual JSON ToJSON();
	virtual void SetVisualPosition(sf::Vector2i pos);
	virtual void FromJSON();
	virtual void RenderPreview();
	virtual void Interact();
	virtual void TryAddGroundItem(int index);
	virtual void Destroy();

	bool CanBePlaced();
	virtual ~Structure();
};

extern int CurrentStructureID;