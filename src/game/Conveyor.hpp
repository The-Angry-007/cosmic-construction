#pragma once
#include "Structure.hpp"

class Conveyor : public Structure
{
public:
	std::vector<int> items;
	int direction;
	float speed;
	sf::Vector2f startPos;
	sf::Vector2f endPos;
	std::vector<float> positions;
	float gap;
	Conveyor(int id, int planetID, int direction);
	void Update(float dt);
	void Render();
	void CollectItems();
	void SetDirection(int direction);
	float progress(sf::Vector2f position);
};