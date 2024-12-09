#include "Chunk.hpp"
#include "Main.hpp"

int CurrentChunkID = 0;

Chunk::Chunk(sf::Vector2i position, int id, int planetID)
{
	if (id == -1)
	{
		this->id = CurrentChunkID++;
	}
	else
	{
		this->id = id;
		if (this->id >= CurrentChunkID)
		{
			CurrentChunkID = this->id + 1;
		}
	}
	items = {};
	this->planetID = planetID;
	this->position = position;
}

void Chunk::Update(float dt)
{
	for (int i = 0; i < items.size(); i++)
	{
		items[i].Update(dt);
	}
}
sf::Vector2f Chunk::GetWorldPos(sf::Vector2f position)
{
	return ((sf::Vector2f)position) * (float)CHUNK_SIZE * (float)TILE_SIZE + position;
}
void Chunk::Render()
{
	sf::RectangleShape chunkRect(sf::Vector2f(CHUNK_SIZE * TILE_SIZE, CHUNK_SIZE * TILE_SIZE));
	chunkRect.setFillColor(sf::Color(abs(position.x) * 25, abs(position.y) * 25, 0));
	chunkRect.setPosition(GetWorldPos(sf::Vector2f(0, 0)));
	window->draw(chunkRect);
	for (int i = 0; i < items.size(); i++)
	{
		items[i].Render();
	}
}