#pragma once
#include "ConveyorType.hpp"
class UndergroundExit : public ConveyorType
{
public:
	int startBelt;
	int maxLength;

	UndergroundExit(int id, int planetID, int direction);
	~UndergroundExit();
	void FromJSON(JSON j);
	void Update(float dt);
	void Render();
	void UpdateNeighbours();
	JSON ToJSON();
	void RenderPreview();
	void Destroy();
};
