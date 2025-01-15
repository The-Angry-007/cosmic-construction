#pragma once
#include "Structure.hpp"
class Boulder : public Structure
{
public:
	int health;
	Boulder(int id, int planetID);
	~Boulder();
	void FromJSON(JSON j);
	JSON ToJSON();
	void Update(float dt);
	void Render();
	void Destroy();
};