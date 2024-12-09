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

void Chunk::Render()
{
	for (int i = 0; i < items.size(); i++)
	{
		items[i].Render();
	}
}