#pragma once
#include "ConveyorType.hpp"
extern std::vector<sf::Vector2i> CONVEYOR_OFFSETS;
class Conveyor : public ConveyorType
{
public:
	int currentNeighbourIndex;
	int neighbour;
	std::vector<std::vector<int>> items;
	std::vector<std::vector<float>> progress;

	float speed;
	float gap;
	Conveyor(int id, int planetID, int direction);
	~Conveyor();
	void FromJSON(JSON j);
	void Update(float dt);
	void Render();
	bool ProgressLane(int lane, float dt, bool moveToMain);
	void TryAddGroundItem(int index);
	// void CollectItems();
	void SetDirection(int direction);

	int StructureInFront();
	bool TryAddItem(int index, int direction, float progress);
	float Distance(int direction);
	// void TryInsertItem(int item, float progress);
	void
	UpdateNeighbours();
	JSON ToJSON();
	void RenderPreview();
	void Destroy();
};