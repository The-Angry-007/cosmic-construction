#pragma once
#include "Item.hpp"
//chunks will be chunk_size * tile_size pixels wide
#define CHUNK_SIZE 16
#define TILE_SIZE 32
class Chunk
{
public:
	sf::Vector2i position;
	int id;
	int planetID;
	std::vector<Item> items;
	Chunk(sf::Vector2i position, int id, int planetID);
	void Save();
	void Update(float dt);
	void Render();
	//convert position of an object within a chunk to an absolute position
	sf::Vector2f GetWorldPos(sf::Vector2f position);
};
extern int CurrentChunkID;