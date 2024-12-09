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
	sprite = sf::Sprite(text);
	sprite.setPosition(sf::Vector2f(
						   ((float)position.x + tileSize.x / 2.f) * (float)TILE_SIZE.x,
						   ((float)position.y + tileSize.y / 2.f) * (float)TILE_SIZE.y)
		+ game->planets[planetID].GetChunk(chunkID)->GetWorldPos(sf::Vector2f(0, 0)));
	sprite.setOrigin((sf::Vector2f)text.getSize() / 2.f);
	std::cout << "finished constructor" << std::endl;
}

void Structure::Update(float dt)
{
}
void Structure::Render()
{
	window->draw(sprite);
}