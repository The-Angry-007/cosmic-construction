#include "Conveyor.hpp"
#include "Main.hpp"
#include "ResourceHandler.hpp"
#include "utils.hpp"

std::vector<sf::Vector2i> CONVEYOR_OFFSETS = {
	sf::Vector2i(0, -1),
	sf::Vector2i(1, 0),
	sf::Vector2i(0, 1),
	sf::Vector2i(-1, 0),
};
Conveyor::Conveyor(int id, int planetID, int direction)
{
	SetID(id);
	this->planetID = planetID;
	typeID = 0;
	SetDirection(direction);
	tileSize = ResourceHandler::structureSizes[typeID];
	ResourceHandler::structureAtlas->SetSprite(sprite, 0, direction);
	gap = 0.4f;
	positions = {};
	speed = 0.4f;
	currentNeighbourIndex = 0;
}
void Conveyor::Update(float dt)
{
	CollectItems();
}
void Conveyor::Render()
{
	window->draw(sprite);
	Planet& p = game->planets[planetID];

	for (uint i = 0; i < items.size(); i++)
	{
		sf::Vector2f pos = positions[i];
		pos += (sf::Vector2f)position;
		p.items[items[i]].position = p.worldPos(pos, chunkID);
		p.items[items[i]].Render();
	}
}

void Conveyor::CollectItems()
{
	//only add new items if there is room
	if (positions.size() > 0 && positions[positions.size() - 1].x < gap)
	{
		return;
	}
	auto& allItems = game->planets[planetID].items;
	auto& items = game->planets[planetID].GetChunk(chunkID)->items;
	for (uint i = 0; i < items.size(); i++)
	{
		if (items[i] == game->planets[planetID].draggingItem)
		{
			continue;
		}
		if (allItems[items[i]].GetTilePos() == position)
		{
			positions.push_back(sf::Vector2f(0.f, 0.f));
			this->items.push_back(items[i]);
			allItems[items[i]].parent = id;
			items.erase(items.begin() + i);
			return;
		}
	}
}
void Conveyor::SetDirection(int direction)
{
	this->direction = direction;
}

int Conveyor::StructureInFront()
{
	sf::Vector2i pos = position + CONVEYOR_OFFSETS[direction];
	Chunk* chunk = game->planets[planetID].GetChunk(chunkID);
	pos += chunk->position * CHUNK_SIZE;
	return game->planets[planetID].StructureInPos(pos);
}
