#pragma once
#include "Hitboxes.hpp"
#include "Item.hpp"

//chunks will be chunk_size * tile_size pixels wide
const int CHUNK_SIZE = 32;
const sf::Vector2i TILE_SIZE(32, 32);
const sf::Vector2i CHUNK_SIZE_PIXELS = CHUNK_SIZE * TILE_SIZE;
class Chunk
{
public:
	sf::Vector2i position;
	int id;
	int planetID;
	std::vector<int> structures;
	std::vector<int> items;
	Chunk(sf::Vector2i position, int id, int planetID);
	void Save();
	void Update(float dt);
	bool isVisible();
	void Render();
	Hitbox* hitbox;
	//convert position of an object within a chunk to an absolute position
	sf::Vector2f GetWorldPos(sf::Vector2f position);
};
extern int CurrentChunkID;