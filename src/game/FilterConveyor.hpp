#pragma once
#include "ConveyorType.hpp"
class FilterConveyor : public ConveyorType
{
public:
	float gap;
	int filterItem;
	std::vector<int> neighbours;
	sf::Sprite overlaySprite;
	std::vector<std::vector<int>> items;
	std::vector<std::vector<float>> progress;
	FilterConveyor(int id, int planetID, int direction);
	~FilterConveyor();
	void FromJSON(JSON j);
	void Update(float dt);
	void Render();
	void Progress(float dt);
	void TryAdd();
	void KeepDistance();
	void TryAddGroundItem(int index);
	void SetDirection(int direction);
	bool TryAddItem(int index, int direction, float progress);
	bool CanAddItem(int direction, float progress);
	bool AcceptsItems(int direction);
	float Distance(int direction);
	void UpdateNeighbours();
	JSON ToJSON();
	void RenderPreview();
	void Destroy();
};