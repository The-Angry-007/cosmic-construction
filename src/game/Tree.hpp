#pragma once
#include "Structure.hpp"
class Tree : public Structure
{
public:
	Tree(int id, int planetID);
	Tree(int planetID);
	~Tree();
	void FromJSON(JSON j);
	JSON ToJSON();
	void Update(float dt);
	void Render();
};