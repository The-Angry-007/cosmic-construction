#pragma once
#include "ConveyorType.hpp"
class UndergroundEnter : public ConveyorType
{
public:
	std::vector<int> items;
	std::vector<float> progress;
	int length;
	int endBelt;
	int neighbour;
	sf::Vector2i endBeltPos;
	int maxLength;

	float gap;
	UndergroundEnter(int id, int planetID, int direction);
	~UndergroundEnter();
	void Progress(float dt);
	void TryAdd();
	void KeepDistance();
	void FromJSON(JSON j);
	void Update(float dt);
	void Render();
	bool ProgressLane(float dt);
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