#pragma once
#include "ConveyorType.hpp"
class Distributor : public ConveyorType
{
public:
	int currentInputIndex;
	int currentOutputIndex;
	std::vector<std::vector<int>> items;
	std::vector<std::vector<float>> progress;
	std::vector<int> neighbours;

	float speed;
	float gap;
	Distributor(int id, int planetID, int direction);
	~Distributor();
	void FromJSON(JSON j);
	void Update(float dt);
	void Render();
	bool ProgressLane(int lane, float dt, bool moveToMain);
	void TryAddGroundItem(int index);
	// void CollectItems();
	void SetDirection(int direction);

	int StructureInFront();
	bool TryAddItem(int index, int direction, float progress);
	bool CanAddItem(int direction, float progress);
	bool AcceptsItems(int direction);
	float Distance(int direction);
	// void TryInsertItem(int item, float progress);
	void
	UpdateNeighbours();
	JSON ToJSON();
	void RenderPreview();
	void Destroy();
};