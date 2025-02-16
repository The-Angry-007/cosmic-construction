#pragma once
#include "Camera.hpp"
#include "Chunk.hpp"
#include "Item.hpp"
#include "RenderObject.hpp"
#include "saving.hpp"
#include "structures.hpp"
extern void buildVertexArray(const std::vector<RenderObject>& renderObjects);

class Planet
{
public:
	//0-7 for each planet in the solar system
	int id;
	std::vector<Item> items;
	std::vector<Chunk> chunks;
	std::vector<int> structuresToUpdate;
	std::vector<Structure*> structures;
	std::vector<int> emptyStructureSlots;
	std::vector<int> emptyChunkSlots;
	std::vector<int> emptyItemSlots;
	Camera camera;
	sf::Color backgroundColor;
	int draggingItem;
	int hoveringItem;
	bool updateNeighbours;
	std::string savePath;
	sf::VertexArray vertexArray;

	std::vector<RenderObject> renderObjects;
	void MoveItem(int index);
	Planet(int id);
	void UpdateNeighbours();
	void Init(bool load);
	void GenerateChunk(sf::Vector2i position);
	void GenerateChunksInView();
	void Update(float dt);
	void Render();
	void Save();
	int StructureInPos(sf::Vector2i position);
	bool StructureInArea(sf::Vector2i position, sf::Vector2i size);
	std::vector<int> StructuresInArea(sf::Vector2i position, sf::Vector2i size);
	Chunk* GetChunk(int chunkID);
	int ChunkAtPos(sf::Vector2f position);
	int ChunkAtPos(sf::Vector2i position);
	sf::Vector2i tilePos(sf::Vector2f position);
	sf::Vector2f worldPos(sf::Vector2f tilePos, int chunkID);
	void WorldUpdate(float dt);
	void AddStructure(Structure* s, bool preserveID = false);
	void AddItem(Item& item);
	void RemoveItem(int item);
	void RemoveStructure(int index);
	bool DeductResources(int typeID, sf::Vector2i position);
	void RemoveStructuresInArea(sf::Vector2i position, sf::Vector2i size);
	std::vector<int> TallyResources(sf::Vector2i position, std::vector<int> types);
};
