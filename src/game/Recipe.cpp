#include "Recipe.hpp"

Recipe::Recipe()
{
	id = -1;
	set = false;
	inputTypes = {};
	inputAmounts = {};
	items = {};
	outputTypes = {};
	outputAmounts = {};
}

void Recipe::LoadFromID(int recipeID)
{
}

void Recipe::Update(float dt)
{
}
void Recipe::Destroy(Structure* parent)
{
}
Recipe::~Recipe()
{
}