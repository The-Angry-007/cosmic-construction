#pragma once
#include "Camera.hpp"
#include "Chunk.hpp"
#include "Item.hpp"
#include "RenderObject.hpp"
#include "saving.hpp"
#include "structures.hpp"
class Planet
{
public:
	//0-7 for each planet in the solar system
	int id;
	std::vector<Item> items;
	std::vector<Chunk> chunks;
	std::vector<Structure*> structures;
	Camera camera;
	sf::Color backgroundColor;
	int draggingItem;
	int hoveringItem;
	std::string savePath;

	std::vector<RenderObject> renderObjects;
	void MoveItem(int index);
	Planet(int id);
	void Init(bool load);
	void GenerateChunk(sf::Vector2i position);
	void GenerateChunksInView();
	void Update(float dt);
	void Render();
	void Save();
	int StructureInPos(sf::Vector2i position);
	Chunk* GetChunk(int chunkID);
	int ChunkAtPos(sf::Vector2f position);
	int ChunkAtPos(sf::Vector2i position);
	sf::Vector2i tilePos(sf::Vector2f position);
	sf::Vector2f worldPos(sf::Vector2f tilePos, int chunkID);
};