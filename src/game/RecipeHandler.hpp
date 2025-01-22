#pragma once
#include "gui.hpp"
//basic struct for storing recipe data
struct RecipeData
{
	std::vector<int> inputTypes;
	std::vector<int> inputAmounts;
	std::vector<bool> isFuels;
	std::vector<float> fuelLengths;
	std::vector<int> outputTypes;
	std::vector<int> outputAmounts;
	float craftTime;
	int id;
};
namespace RecipeHandler
{
//2d array, where outside array's index is the structure id and inside is all the recipes for that structure
extern std::vector<std::vector<RecipeData>> recipes;
extern GUI* gui;
extern int guiStructure;
extern int numBgObjs;
void Update(float dt);
void InitGUI(int structure);
void LoadRecipes(std::vector<JSON> jsons);
RecipeData* GetRecipe(int id);

};