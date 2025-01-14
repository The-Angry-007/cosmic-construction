#pragma once
#include "Structure.hpp"
class TreeChopper : public Structure
{
public:
	int direction;
	float timeSinceAction;
	int phase;
	TreeChopper(int id, int planetID, int direction);
	~TreeChopper();
	void Update(float dt);
	void Render();
	void RenderPreview();
};