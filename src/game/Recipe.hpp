#pragma once
#include "Structure.hpp"
#include "gui.hpp"

class Structure;
class Recipe
{
public:
	RecipeData* data;
	int planetID;
	std::vector<float> fuelsLeft;
	std::vector<std::vector<int>> inputItems;
	std::vector<std::vector<int>> outputItems;
	float craftTimer;
	Recipe(int planetID, RecipeData* data);
	void Update(float dt);
	bool TryAddItem(int index);
	int TryTakeItem();
	void Destroy(Structure* parent);
	~Recipe();
};