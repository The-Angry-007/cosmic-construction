#pragma once
#include "Hitboxes.hpp"
#include "saving.hpp"
class Recipe;
struct RecipeData;
class Structure
{
public:
	int typeID;
	int id;
	int chunkID = -1;
	int planetID;
	int zindex;
	bool blocksItems;
	Recipe* recipe = nullptr;
	bool placedByPlayer;
	bool isConveyor = false;
	bool isTerrain = false;
	bool isFlipped = false;
	sf::Vector2i bottomRightPos;
	sf::Vector2i position;
	sf::Vector2i tileSize;
	sf::Sprite sprite;
	int direction = 0;
	Hitbox* hitbox;
	Structure();
	virtual void Update(float dt);
	virtual void UpdateNeighbours();
	virtual void Render();
	virtual void SetPosition(sf::Vector2i position);
	void SetID(int id);
	virtual JSON ToJSON();
	virtual void SetVisualPosition(sf::Vector2i pos);
	virtual void FromJSON();
	virtual void RenderPreview();
	virtual void Interact();
	virtual void TryAddGroundItem(int index);
	virtual bool TryAddItem(int index);
	virtual void Destroy();
	virtual void SetDirection(int direction);
	virtual void SetRecipe(RecipeData* data);
	virtual void SetFlipped(bool flipped);

	bool CanBePlaced();
	virtual ~Structure();
};

extern int CurrentStructureID;