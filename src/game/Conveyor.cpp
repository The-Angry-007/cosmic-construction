#include "Conveyor.hpp"
#include "Main.hpp"
#include "ResourceHandler.hpp"
Conveyor::Conveyor(int id, int planetID, int direction)
{
	SetID(id);
	this->planetID = planetID;
	typeID = 0;
	this->direction = direction;
	tileSize = ResourceHandler::structureSizes[typeID];
	ResourceHandler::structureAtlas->SetSprite(sprite, direction);
}
void Conveyor::Update(float dt)
{
	CollectItems();
}
void Conveyor::Render()
{
	window->draw(sprite);
}

void Conveyor::CollectItems()
{
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
			this->items.push_back(items[i]);
			allItems[items[i]].parent = id;
			items.erase(items.begin() + i);
			i--;
		}
	}
}
