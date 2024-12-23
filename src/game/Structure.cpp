#include "Structure.hpp"
#include "Chunk.hpp"
#include "Main.hpp"
#include "ResourceHandler.hpp"
int CurrentStructureID = 0;
Structure::Structure()
{

	// this->chunkID = chunkID;
	// this->planetID = planetID;
	// this->typeID = typeID;
	// this->position = position;

	// tileSize = ResourceHandler::structureSizes[typeID];
	// sf::Texture& text = ResourceHandler::structureTextures[typeID];
	// sprite = sf::Sprite(text);
	// sprite.setPosition(sf::Vector2f(
	// 					   ((float)position.x + tileSize.x / 2.f) * (float)TILE_SIZE.x,
	// 					   ((float)position.y + tileSize.y / 2.f) * (float)TILE_SIZE.y)
	// 	+ game->planets[planetID].GetChunk(chunkID)->GetWorldPos(sf::Vector2f(0, 0)));
	// sprite.setOrigin((sf::Vector2f)text.getSize() / 2.f);
	// std::cout << "finished constructor" << std::endl;
}

void Structure::SetID(int id)
{
	if (id == -1)
	{
		this->id = CurrentStructureID++;
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
		if (game->planets[planetID].structures[i]->id == id)
		{
			index = i;
			break;
		}
	}
	auto& chunks = game->planets[planetID].chunks;
	int i = game->planets[planetID].ChunkAtPos(position);
	chunkID = chunks[i].id;
	chunks[i].structures.push_back(index);
	this->position = sf::Vector2i(position.x - chunks[i].position.x * CHUNK_SIZE, position.y - chunks[i].position.y * CHUNK_SIZE);
	bottomRightPos = this->position + tileSize - sf::Vector2i(1, 1);
	sf::Vector2f pos2 = (sf::Vector2f)this->position + (sf::Vector2f)tileSize / 2.f;
	sf::Vector2f pos = game->planets[planetID].worldPos(pos2, chunks[i].id);
	sprite.setPosition(pos);
}

JSON Structure::ToJSON()
{
	return JSON();
}

void Structure::FromJSON()
{
}