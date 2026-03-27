#include "Recipe.hpp"
#include "../Main.hpp"
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
	//if craft is being executed:
	if (craftTimer > 0)
	{
		craftTimer -= dt;
		//if craft has ended then try and fill up the outputs, if no more room then extend the craft timer a bit
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
		//otherwise, try and start a craft
		//deplete fuels
		for (int i = 0; i < fuelsLeft.size(); i++)
		{
			if (data->isFuels[i] && fuelsLeft[i] <= 1.f && numInputs[i] >= data->inputAmounts[i])
			{
				numInputs[i] -= data->inputAmounts[i];
				fuelsLeft[i] += data->fuelLengths[i];
			}
		}
		bool canCraft = true;
		//check there are enough items
		for (int i = 0; i < numInputs.size(); i++)
		{
			if ((data->isFuels[i] && fuelsLeft[i] <= 0.01f) || (!data->isFuels[i] && numInputs[i] < data->inputAmounts[i]))
			{
				canCraft = false;
				break;
			}
		}
		//if can craft, deduct resources required
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

//place input and output items on ground in area the size of the parent structure
void Recipe::Destroy(Structure* parent)
{
	sf::Vector2i position = parent->position;
	sf::Vector2i tileSize = parent->tileSize;
	for (int i = 0; i < numInputs.size(); i++)
	{
		for (int j = 0; j < numInputs[i]; j++)
		{
			Item item = Item(sf::Vector2f(0.f, 0.f), -1, data->inputTypes[i]);
			item.SetParent(-1);
			item.position = (sf::Vector2f)(position + game->planets[planetID].GetChunk(parent->chunkID)->position * CHUNK_SIZE);
			item.position += sf::Vector2f(rand() % 1000 * tileSize.x, rand() % 1000 * tileSize.y) / 1000.f;
			item.position.x *= TILE_SIZE.x;
			item.position.y *= TILE_SIZE.y;
			game->planets[planetID].AddItem(item);

			game->planets[planetID].MoveItem(item.id);
		}
	}
	for (int i = 0; i < numOutputs.size(); i++)
	{
		for (int j = 0; j < numOutputs[i]; j++)
		{
			Item item = Item(sf::Vector2f(0.f, 0.f), -1, data->outputTypes[i]);
			item.SetParent(-1);
			item.position = (sf::Vector2f)(position + game->planets[planetID].GetChunk(parent->chunkID)->position * CHUNK_SIZE);
			item.position += sf::Vector2f(rand() % 1000 * tileSize.x, rand() % 1000 * tileSize.y) / 1000.f;
			item.position.x *= TILE_SIZE.x;
			item.position.y *= TILE_SIZE.y;
			game->planets[planetID].AddItem(item);

			game->planets[planetID].MoveItem(item.id);
		}
	}
}
//checks if the type id matches one of the inputs and there is enough room to add the item
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
//removes one of the output items if there are any
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
//adds attributes to JSON, each attribute starts with recipe to prevent conflicts with parent
JSON Recipe::ToJSON()
{
	JSON j = JSON();
	j.AddAttribute("RecipeID", data->id);
	j.AddAttribute("RecipeNumInputs", numInputs);
	j.AddAttribute("RecipeNumOutputs", numOutputs);
	j.AddAttribute("RecipeFuelsLeft", fuelsLeft);
	j.AddAttribute("RecipePlanetID", planetID);
	j.AddAttribute("RecipeCraftTimer", craftTimer);
	return j;
}
//loads from JSON boject
void Recipe::FromJSON(JSON j)
{
	numInputs = j.GetIntArr("RecipeNumInputs");
	numOutputs = j.GetIntArr("RecipeNumOutputs");
	fuelsLeft = j.GetFloatArr("RecipeFuelsLeft");
	planetID = j.GetInt("RecipePlanetID");
	craftTimer = j.GetFloat("RecipeCraftTimer");
}