#pragma once
#include "ConveyorType.hpp"
class Underground : public ConveyorType
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
	Underground(int id, int planetID, int direction);
	~Underground();
	void Progress(float dt);
	void TryAdd();
	void KeepDistance();
	void FromJSON(JSON j);
	void Update(float dt);
	void Render();
	void SetFlipped(bool flipped);
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