#pragma once
#include "Structure.hpp"
extern std::vector<sf::Vector2i> CONVEYOR_OFFSETS;
class Conveyor : public Structure
{
public:
	int currentNeighbourIndex;
	std::vector<int> neighbours;
	std::vector<int> inputs;
	std::vector<int> items;
	std::vector<sf::Vector2f> positions;

	int direction;
	float speed;
	float gap;
	Conveyor(int id, int planetID, int direction);
	void Update(float dt);
	void Render();
	void CollectItems();
	void SetDirection(int direction);
	int StructureInFront();
	bool GetAdjacentItems(int dir);
	void TryInsertItem(int item, float progress);
	void UpdateNeighbours();
};