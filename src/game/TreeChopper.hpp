#pragma once
#include "Structure.hpp"
class TreeChopper : public Structure
{
public:
	float timeSinceAction;
	int phase;
	TreeChopper(int id, int planetID, int direction);
	~TreeChopper();
	void Update(float dt);
	void Render();
	void RenderPreview();
	JSON ToJSON();
	void FromJSON(JSON j);
	void SetDirection(int direction);
};