#include "Recipe.hpp"
#include "Main.hpp"
#include "RecipeHandler.hpp"
Recipe::Recipe(int planetID, RecipeData* data)
{
	this->planetID = planetID;
	this->data = data;
	fuelsLeft = {};
	numInputs = {};
	numOutputs = {};
	for (int i = 0; i < data->inputTypes.size(); i++)
	{
		numInputs.push_back(0);
	}
	for (int i = 0; i < data->outputTypes.size(); i++)
	{
		numOutputs.push_back(0);
	}
	for (int i = 0; i < data->fuelLengths.size(); i++)
	{
		fuelsLeft.push_back(0.f);
	}
	craftTimer = 0.f;
}

void Recipe::Update(float dt)
{
	if (craftTimer > 0)
	{
		craftTimer -= dt;
		if (craftTimer <= 0.f)
		{
			float maxMult = 0.f;
			for (int i = 0; i < numOutputs.size(); i++)
			{
				float mult = numOutputs[i] / (float)(data->outputAmounts[i]);
				if (mult > maxMult)
				{
					maxMult = mult;
				}
			}
			if (maxMult < 5.f)
			{
				for (int i = 0; i < numOutputs.size(); i++)
				{
					numOutputs[i] += data->outputAmounts[i];
					// Item item = Item(sf::Vector2f(0.f, 0.f), -1, data->outputTypes[i]);
					// item.SetParent(1);
					// game->planets[planetID].items.push_back(item);
					// outputItems[i].push_back(game->planets[planetID].items.size() - 1);
				}
			}
			else
			{
				craftTimer += dt;
			}
		}
	}
	else
	{
		for (int i = 0; i < fuelsLeft.size(); i++)
		{
			if (data->isFuels[i] && fuelsLeft[i] <= 1.f && numInputs[i] > 0)
			{
				numInputs[i]--;
				// game->planets[planetID].items[inputItems[i].back()].isDeleted = true;
				// inputItems[i].pop_back();
				fuelsLeft[i] += data->fuelLengths[i];
			}
		}
		bool canCraft = true;
		for (int i = 0; i < numInputs.size(); i++)
		{
			if ((data->isFuels[i] && fuelsLeft[i] <= 0.01f) || (!data->isFuels[i] && numInputs[i] < data->inputAmounts[i]))
			{
				canCraft = false;
				break;
			}
		}
		if (canCraft)
		{
			craftTimer = data->craftTime;
			Planet& p = game->planets[planetID];
			for (int i = 0; i < numInputs.size(); i++)
			{
				if (data->isFuels[i])
				{
					fuelsLeft[i] -= data->craftTime;
					continue;
				}
				numInputs[i] -= data->inputAmounts[i];
			}
		}
	}
}

// for (int i = 0; i < fuelsLeft.size(); i++)
// {
// 	if (craftTimer > dt)
// 		fuelsLeft[i] -= dt;
// 	if (fuelsLeft[i] < 0)
// 	{
// 		if (inputItems[i].size() > 0)
// 		{
// 			game->planets[planetID].items[inputItems[i].back()].isDeleted = true;
// 			inputItems[i].pop_back();
// 			fuelsLeft[i] = data->fuelLengths[i];
// 		}
// 	}
// }
//}
void Recipe::Destroy(Structure* parent)
{
	sf::Vector2i position = parent->position;
	sf::Vector2i tileSize = parent->tileSize;
	for (int i = 0; i < numInputs.size(); i++)
	{
		for (int j = 0; j < numInputs[i]; j++)
		{
			// Item& item = game->planets[planetID].items[inputItems[i][j]];
			Item item = Item(sf::Vector2f(0.f, 0.f), -1, data->inputTypes[i]);
			game->planets[planetID].AddItem(item);
			item.SetParent(-1);
			item.position = (sf::Vector2f)(position + game->planets[planetID].GetChunk(parent->chunkID)->position * CHUNK_SIZE);
			item.position += sf::Vector2f(rand() % 1000 * tileSize.x, rand() % 1000 * tileSize.y) / 1000.f;
			item.position.x *= TILE_SIZE.x;
			item.position.y *= TILE_SIZE.y;
			game->planets[planetID].MoveItem(item.id);
		}
	}
	for (int i = 0; i < numOutputs.size(); i++)
	{
		for (int j = 0; j < numOutputs[i]; j++)
		{
			// Item& item = game->planets[planetID].items[outputItems[i][j]];
			Item item = Item(sf::Vector2f(0.f, 0.f), -1, data->outputTypes[i]);
			game->planets[planetID].AddItem(item);
			item.SetParent(-1);
			item.position = (sf::Vector2f)(position + game->planets[planetID].GetChunk(parent->chunkID)->position * CHUNK_SIZE);
			item.position += sf::Vector2f(rand() % 1000 * tileSize.x, rand() % 1000 * tileSize.y) / 1000.f;
			item.position.x *= TILE_SIZE.x;
			item.position.y *= TILE_SIZE.y;
			game->planets[planetID].MoveItem(item.id);
		}
	}
}
bool Recipe::TryAddItem(int index)
{
	Item& item = game->planets[planetID].items[index];
	for (int i = 0; i < data->inputTypes.size(); i++)
	{
		if (item.typeId == data->inputTypes[i])
		{
			if (numInputs[i] < data->inputAmounts[i] * 3)
			{
				game->planets[planetID].RemoveItem(index);
				numInputs[i]++;
				return true;
			}
		}
	}
	return false;
}
int Recipe::TryTakeItem()
{
	for (int i = 0; i < numOutputs.size(); i++)
	{
		if (numOutputs[i] > 0)
		{
			Item item = Item(sf::Vector2f(0.f, 0.f), -1, data->outputTypes[i]);
			game->planets[planetID].AddItem(item);
			item.SetParent(1);
			numOutputs[i]--;
			return item.id;
		}
	}
	return -1;
}
Recipe::~Recipe()
{
}

JSON Recipe::ToJSON()
{
	JSON j = JSON();
	j.AddAttribute("RecipeID", data->id);
	j.AddAttribute("RecipeNumInputs", numInputs);
	j.AddAttribute("RecipeNumOutputs", numOutputs);
	// for (int i = 0; i < numInputs.size(); i++)
	// {
	// 	j.AddAttribute("RecipeNumInputs" + std::to_string(i), numInputs[i]);
	// }
	// for (int i = 0; i < outputItems.size(); i++)
	// {
	// 	j.AddAttribute("RecipeOutputItems" + std::to_string(i), outputItems[i]);
	// }
	j.AddAttribute("RecipeFuelsLeft", fuelsLeft);
	j.AddAttribute("RecipePlanetID", planetID);
	j.AddAttribute("RecipeCraftTimer", craftTimer);
	return j;
}

void Recipe::FromJSON(JSON j)
{
	numInputs = j.GetIntArr("RecipeNumInputs");
	numOutputs = j.GetIntArr("RecipeNumOutputs");
	// for (int i = 0; i < inputItems.size(); i++)
	// {
	// 	inputItems[i] = j.GetIntArr("RecipeInputItems" + std::to_string(i));
	// }
	// for (int i = 0; i < outputItems.size(); i++)
	// {
	// 	outputItems[i] = j.GetIntArr("RecipeOutputItems" + std::to_string(i));
	// }
	fuelsLeft = j.GetFloatArr("RecipeFuelsLeft");
	planetID = j.GetInt("RecipePlanetID");
	craftTimer = j.GetFloat("RecipeCraftTimer");
}