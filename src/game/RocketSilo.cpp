#include "RocketSilo.hpp"
#include "Main.hpp"
#include "Recipe.hpp"
#include "RecipeHandler.hpp"
#include "ResourceHandler.hpp"
RocketSilo::RocketSilo(int id, int planetID, int direction, int typeID)
{
	SetID(id);
	this->planetID = planetID;
	this->typeID = typeID;
	tileSize = ResourceHandler::structureSizes[typeID];
	sprite = sf::Sprite();
	ResourceHandler::structureAtlas->SetSprite(sprite, typeID, 0);

	blocksItems = true;
	placedByPlayer = true;
	launchType = -1;
}

RocketSilo::~RocketSilo()
{}

void RocketSilo::UpdateNeighbours()
{
}

void RocketSilo::Update(float dt)
{
	// if (recipe != nullptr)
	// {
	// 	recipe->Update(dt);
	// }
	// std::vector<int> directions = {
	// 	2, 2, 3, 3, 0, 0, 1, 1
	// };
	// // if (outputItem == -1 && recipe != nullptr)
	// // {
	// // 	outputItem = recipe->TryTakeItem();
	// // }
	// if (recipe != nullptr)
	// {
	// 	for (int i = 0; i < 8; i++)
	// 	{
	// 		int index = (i + lastOutputDir) % 8;
	// 		if (neighbours[index] != -1)
	// 		{
	// 			ConveyorType* c = dynamic_cast<ConveyorType*>(game->planets[planetID].structures[neighbours[index]]);
	// 			int dir = directions[index];

	// 			if (c->CanAddItem(dir, 0.f))
	// 			{
	// 				outputItem = recipe->TryTakeItem();
	// 				if (outputItem != -1)
	// 				{
	// 					c->TryAddItem(outputItem, dir, 0.f);
	// 					outputItem = -1;
	// 					lastOutputDir = (index + 1) % 8;
	// 					break;
	// 				}
	// 			}
	// 		}
	// 	}
	// }
}

void RocketSilo::Render()
{
	game->planets[planetID].renderObjects.push_back(RenderObject {
		&sprite,
		32 });
}

void RocketSilo::Destroy()
{
	if (recipe != nullptr)
	{
		recipe->Destroy(this);
	}
}
void RocketSilo::SetPosition(sf::Vector2i position)
{
	Structure::SetPosition(position);
}
void RocketSilo::RenderPreview()
{
	int opacity = 100;
	sf::Color col = sf::Color::Green;

	if (!CanBePlaced())
	{
		col = sf::Color(255, 100, 100);
	}
	col.a = opacity;
	sprite.setColor(col);
	Planet& p = game->planets[planetID];
	p.renderObjects.push_back(RenderObject {
		&sprite,
		2000 });
}

JSON RocketSilo::ToJSON()
{
	JSON j = JSON();
	j.AddAttribute("Position", position);
	j.AddAttribute("TypeID", typeID);
	j.AddAttribute("ChunkID", chunkID);
	j.AddAttribute("ID", id);
	if (recipe != nullptr)
	{
		j.AddAttribute("HasRecipe", 1);
		j.AddJSON(recipe->ToJSON());
	}
	else
	{
		j.AddAttribute("HasRecipe", 0);
	}
	return j;
}
void RocketSilo::FromJSON(JSON j)
{
	sf::Vector2i pos = j.GetV2i("Position");
	chunkID = j.GetInt("ChunkID");
	id = j.GetInt("ID");
	pos += game->planets[planetID].GetChunk(chunkID)->position * CHUNK_SIZE;
	SetPosition(pos);
	if (j.GetInt("HasRecipe"))
	{
		int id = j.GetInt("RecipeID");
		recipe = new Recipe(planetID, RecipeHandler::GetRecipe(id));
		recipe->FromJSON(j);
	}
}

void RocketSilo::SetVisualPosition(sf::Vector2i position)
{
	Structure::SetVisualPosition(position);
}

void RocketSilo::Interact()
{
	int index = -1;
	Planet& p = game->planets[planetID];
	for (int i = 0; i < p.structures.size(); i++)
	{
		if (p.structures[i] == this)
		{
			index = i;
			break;
		}
	}
	RecipeHandler::InitGUI(index);
}

bool RocketSilo::TryAddItem(int index)
{
	if (recipe == nullptr)
	{
		return false;
	}
	return recipe->TryAddItem(index);
}