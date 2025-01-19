#pragma once
#include "Structure.hpp"
extern std::vector<sf::Vector2i> CONVEYOR_OFFSETS;
class Conveyor : public Structure
{
public:
	int currentNeighbourIndex;
	std::vector<int> neighbours;
	std::vector<std::vector<int>> items;
	std::vector<std::vector<float>> progress;

	float speed;
	float gap;
	Conveyor(int id, int planetID, int direction);
	~Conveyor();
	void FromJSON(JSON j);
	void Update(float dt);
	void Render();
	void ProgressLane(int lane, float dt);
	void TryAddGroundItem(int index);
	// void CollectItems();
	void SetDirection(int direction);

	int StructureInFront();
	bool GetAdjacentItems(int dir);
	void TryInsertItem(int item, float progress);
	void UpdateNeighbours();
	JSON ToJSON();
	void RenderPreview();
	void Destroy();
};