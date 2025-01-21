#pragma once
#include "Structure.hpp"
#include "gui.hpp"
class Structure;
class Recipe
{
public:
	int id;
	std::vector<int> inputTypes;
	std::vector<int> inputAmounts;
	std::vector<int> items;
	std::vector<int> outputTypes;
	std::vector<int> outputAmounts;
	bool set;
	Recipe();
	void LoadFromID(int recipeID);
	void Update(float dt);
	void Destroy(Structure* parent);
	~Recipe();
};