#include "Structure.hpp"
#include "Chunk.hpp"
#include "Main.hpp"
#include "ResourceHandler.hpp"
int CurrentStructureID = 0;
Structure::Structure(sf::Vector2i position, int typeID, int id, int chunkID, int planetID)
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
	this->chunkID = chunkID;
	this->planetID = planetID;
	this->typeID = typeID;
	this->position = position;
	tileSize = ResourceHandler::structureSizes[typeID];
	sf::Texture& text = ResourceHandler::structureTextures[typeID];
	sprite.setTexture(text);
	sprite.setPosition(sf::Vector2f(
						   (position.x + tileSize.x / 2.f) * TILE_SIZE.x,
						   (position.y + tileSize.y / 2.f) * TILE_SIZE.y)
		+ game->planets[planetID].GetChunk(chunkID)->GetWorldPos(sf::Vector2f(0, 0)));
	sprite.setOrigin(sf::Vector2f(
		tileSize.x / 2.f * TILE_SIZE.x,
		tileSize.y / 2.f * TILE_SIZE.y));
}

void Structure::Update(float dt)
{
}
void Structure::Render()
{
	window->draw(sprite);
}