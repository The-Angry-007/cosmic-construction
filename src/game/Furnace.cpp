#include "Furnace.hpp"
#include "Main.hpp"
#include "Recipe.hpp"
#include "RecipeHandler.hpp"
#include "ResourceHandler.hpp"
Furnace::Furnace(int id, int planetID, int direction)
{
	SetID(id);
	this->planetID = planetID;
	typeID = 7;
	tileSize = ResourceHandler::structureSizes[typeID];
	sprite = sf::Sprite();
	ResourceHandler::structureAtlas->SetSprite(sprite, typeID, 0);

	blocksItems = true;
	placedByPlayer = true;
	numStone = 0;
	neighbours = {};
	lastOutputDir = 0;
	outputItem = -1;
}

Furnace::~Furnace()
{}

void Furnace::UpdateNeighbours()
{
	std::vector<sf::Vector2i> offsets = {
		{ 0, -1 },
		{ 1, -1 },
		{ 2, 0 },
		{ 2, 1 },
		{ 1, 2 },
		{ 0, 2 },
		{ -1, 1 },
		{ -1, 0 }
	};
	std::vector<int> directions = {
		2, 2, 3, 3, 0, 0, 1, 1
	};
	if (recipe != nullptr && recipe->craftTimer > 0.f)
	{
		ResourceHandler::structureAtlas->SetSprite(sprite, typeID, 1);
	}
	else
	{
		ResourceHandler::structureAtlas->SetSprite(sprite, typeID, 0);
	}
	neighbours = {};
	Planet& p = game->planets[planetID];
	sf::Vector2i pos = position + p.GetChunk(chunkID)->position * CHUNK_SIZE;
	for (int i = 0; i < offsets.size(); i++)
	{
		sf::Vector2i newPos = pos + offsets[i];
		int structure = p.StructureInPos(newPos);
		if (structure != -1)
		{
			Structure* s = p.structures[structure];
			if (s->typeID == 0 && s->direction != ((directions[i]) % 4))
			{
				neighbours.push_back(structure);
			}
			else
			{
				neighbours.push_back(-1);
			}
		}
		else
		{
			neighbours.push_back(-1);
		}
	}
}

void Furnace::Update(float dt)
{
	UpdateNeighbours();
	if (recipe != nullptr)
	{
		recipe->Update(dt);
	}
	std::vector<int> directions = {
		2, 2, 3, 3, 0, 0, 1, 1
	};
	// if (outputItem == -1 && recipe != nullptr)
	// {
	// 	outputItem = recipe->TryTakeItem();
	// }
	if (recipe != nullptr)
	{
		for (int i = 0; i < 8; i++)
		{
			int index = (i + lastOutputDir) % 8;
			if (neighbours[index] != -1)
			{
				ConveyorType* c = dynamic_cast<ConveyorType*>(game->planets[planetID].structures[neighbours[index]]);
				int dir = directions[index];

				if (c->CanAddItem(dir, 0.f))
				{
					outputItem = recipe->TryTakeItem();
					if (outputItem != -1)
					{
						c->TryAddItem(outputItem, dir, 0.f);
						outputItem = -1;
						lastOutputDir = (index + 1) % 8;
						break;
					}
				}
			}
		}
	}
}

void Furnace::Render()
{
	game->planets[planetID].renderObjects.push_back(RenderObject {
		&sprite,
		32 });
}

void Furnace::Destroy()
{
	if (recipe != nullptr)
	{
		recipe->Destroy(this);
	}
}
void Furnace::SetPosition(sf::Vector2i position)
{
	Structure::SetPosition(position);
}
void Furnace::RenderPreview()
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

JSON Furnace::ToJSON()
{
	JSON j = JSON();
	j.AddAttribute("Position", position);
	j.AddAttribute("TypeID", typeID);
	j.AddAttribute("ChunkID", chunkID);
	j.AddAttribute("ID", id);
	j.AddAttribute("NumStone", numStone);
	j.AddAttribute("LastOutputDir", lastOutputDir);
	j.AddAttribute("OutputItem", outputItem);
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
void Furnace::FromJSON(JSON j)
{
	sf::Vector2i pos = j.GetV2i("Position");
	chunkID = j.GetInt("ChunkID");
	id = j.GetInt("ID");
	pos += game->planets[planetID].GetChunk(chunkID)->position * CHUNK_SIZE;
	SetPosition(pos);
	numStone = j.GetInt("NumStone");
	lastOutputDir = j.GetInt("LastOutputDir");
	outputItem = j.GetInt("OutputItem");
	if (j.GetInt("HasRecipe"))
	{
		int id = j.GetInt("RecipeID");
		recipe = new Recipe(planetID, RecipeHandler::GetRecipe(id));
		recipe->FromJSON(j);
	}
}

void Furnace::SetVisualPosition(sf::Vector2i position)
{
	Structure::SetVisualPosition(position);
}

void Furnace::Interact()
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

bool Furnace::TryAddItem(int index)
{
	if (recipe == nullptr)
	{
		return false;
	}
	return recipe->TryAddItem(index);
}