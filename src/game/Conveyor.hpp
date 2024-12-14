#pragma once
#include "Structure.hpp"

class Conveyor : public Structure
{
public:
	std::vector<int> items;
	int direction;
	Conveyor(int id, int planetID, int direction);
	void Update(float dt);
	void Render();
};