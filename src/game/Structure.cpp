#include "Structure.hpp"
#include "Chunk.hpp"
#include "Main.hpp"
#include "Recipe.hpp"
#include "RecipeHandler.hpp"
#include "ResourceHandler.hpp"
int CurrentStructureID = 0;
Structure::Structure()
{
}
void Structure::SetID(int id)
{
	if (id == -1)
	{
		this->id = CurrentStructureID++;
	}
	else if (id == -2)
	{
		this->id = -CurrentStructureID;
	}
	else
	{
		this->id = id;
		if (this->id >= CurrentStructureID)
		{
			CurrentStructureID = this->id + 1;
		}
	}
}

void Structure::Update(float dt)
{
}
void Structure::Render()
{
	window->draw(sprite);
}

void Structure::SetPosition(sf::Vector2i position)
{
	int index;
	for (uint i = 0; i < game->planets[planetID].structures.size(); i++)
	{
		if (game->planets[planetID].structures[i] != nullptr && game->planets[planetID].structures[i]->id == id)
		{
			index = i;
			break;
		}
	}
	auto& chunks = game->planets[planetID].chunks;
	if (chunkID != -1)
	{
		auto& structures = game->planets[planetID].GetChunk(chunkID)->structures;
		for (int i = 0; i < structures.size(); i++)
		{
			if (structures[i] == index)
			{
				structures.erase(structures.begin() + i);
				break;
			}
		}
	}
	int i = game->planets[planetID].ChunkAtPos(position);
	chunkID = chunks[i].id;
	chunks[i].structures.push_back(index);
	if (!isTerrain)
	{
		chunks[i].isAltered = true;
	}
	this->position = sf::Vector2i(position.x - chunks[i].position.x * CHUNK_SIZE, position.y - chunks[i].position.y * CHUNK_SIZE);
	bottomRightPos = this->position + tileSize - sf::Vector2i(1, 1);
	sf::Vector2f pos2 = (sf::Vector2f)this->position + (sf::Vector2f)tileSize / 2.f;
	sf::Vector2f pos = game->planets[planetID].worldPos(pos2, chunks[i].id);
	sprite.setPosition(pos);
	game->planets[planetID].UpdateNeighbours();
}
void Structure::TryAddGroundItem(int index)
{}
JSON Structure::ToJSON()
{
	return JSON();
}

void Structure::FromJSON()
{
}

Structure::~Structure()
{
	// delete hitbox;
}

void Structure::UpdateNeighbours()
{
}

bool Structure::CanBePlaced()
{
	sf::Vector2i pos = position + game->planets[planetID].GetChunk(chunkID)->position * CHUNK_SIZE;
	return !(game->planets[planetID].StructureInArea(pos, tileSize));
}

void Structure::RenderPreview()
{
	std::cout << "i should not be called" << std::endl;
}

void Structure::SetVisualPosition(sf::Vector2i pos)
{
	auto& chunks = game->planets[planetID].chunks;

	int i = game->planets[planetID].ChunkAtPos(pos);
	this->chunkID = chunks[i].id;
	this->position = sf::Vector2i(pos.x - chunks[i].position.x * CHUNK_SIZE, pos.y - chunks[i].position.y * CHUNK_SIZE);
	sf::Vector2f p2(pos.x + tileSize.x / 2.f, pos.y + tileSize.y / 2.f);
	sf::Vector2f p(p2.x * TILE_SIZE.x, p2.y * TILE_SIZE.y);
	sprite.setPosition(p);
}

void Structure::Interact()
{}

void Structure::Destroy()
{}

void Structure::SetDirection(int direction)
{}

bool Structure::TryAddItem(int index)
{
	return false;
}

void Structure::SetRecipe(RecipeData* data)
{
	if (recipe != nullptr)
	{
		delete recipe;
	}
	recipe = new Recipe(planetID, data);
}