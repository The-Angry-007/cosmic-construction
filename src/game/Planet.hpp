#pragma once
#include "Camera.hpp"
#include "Chunk.hpp"
#include "Item.hpp"
#include "saving.hpp"
class Planet
{
public:
	//0-7 for each planet in the solar system
	int id;
	std::vector<Chunk> chunks;
	Camera camera;
	sf::Color backgroundColor;
	int draggingItem;
	int draggingChunk;
	std::string savePath;
	sf::Vector2f mouseStartDraggingPos;
	sf::Vector2f itemStartDraggingPos;
	Planet(int id, bool load);
	void GenerateChunk(sf::Vector2i position);
	void GenerateChunksInView();
	void Update(float dt);
	void Render();
	void Save();
};