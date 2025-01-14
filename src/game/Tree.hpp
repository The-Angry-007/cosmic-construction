#pragma once
#include "Structure.hpp"
class Tree : public Structure
{
public:
	int health;
	int parent;
	Tree(int id, int planetID);
	~Tree();
	void FromJSON(JSON j);
	JSON ToJSON();
	void Update(float dt);
	void Render();
	void Destroy();
};