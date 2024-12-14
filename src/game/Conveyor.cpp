#include "Conveyor.hpp"
#include "Main.hpp"
#include "ResourceHandler.hpp"
#include "utils.hpp"
Conveyor::Conveyor(int id, int planetID, int direction)
{
	SetID(id);
	this->planetID = planetID;
	typeID = 0;
	SetDirection(direction);
	tileSize = ResourceHandler::structureSizes[typeID];
	ResourceHandler::structureAtlas->SetSprite(sprite, direction);
	gap = 0.1f;
	positions = {};
	speed = 0.2f;
}
void Conveyor::Update(float dt)
{
	for (uint i = 0; i < positions.size(); i++)
	{
		if (i == positions.size() - 1)
		{
			positions[i] += dt * speed;
			if (positions[i] > 1.f)
			{
				positions[i] = 1.f;
			}
		}
		else
		{
			positions[i] += dt * speed;

			if (positions[i + 1] - positions[i] < gap)
			{
				positions[i] = positions[i + 1] - gap;
			}
		}
	}
	CollectItems();
}
void Conveyor::Render()
{
	window->draw(sprite);
	Planet& p = game->planets[planetID];
	sf::Vector2f startPos = this->startPos + (sf::Vector2f)position;
	sf::Vector2f endPos = this->startPos + (sf::Vector2f)position;
	startPos = p.worldPos(startPos, chunkID);
	endPos = p.worldPos(startPos, chunkID);
	for (uint i = 0; i < items.size(); i++)
	{
		p.items[items[i]].position = Lerp(startPos, endPos, positions[i]);
		p.items[items[i]].Render();
	}
}

void Conveyor::CollectItems()
{
	//only add new items if there is room
	if (positions.size() > 0 && positions[positions.size() - 1] < gap)
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
			positions.push_back(0.f);
			this->items.push_back(items[i]);
			allItems[items[i]].parent = id;
			items.erase(items.begin() + i);
			i--;
		}
	}
}
void Conveyor::SetDirection(int direction)
{
	this->direction = direction;
	if (direction == 0)
	{
		startPos = sf::Vector2f(0.5f, 1.f);
		endPos = sf::Vector2f(0.5f, 0.f);
	}
	else if (direction == 1)
	{
		startPos = sf::Vector2f(0.f, 0.5f);
		endPos = sf::Vector2f(1.f, 0.5f);
	}
	else if (direction == 2)
	{
		startPos = sf::Vector2f(0.5f, 0.f);
		endPos = sf::Vector2f(0.5f, 1.f);
	}
	else
	{
		startPos = sf::Vector2f(1.f, 0.5f);
		endPos = sf::Vector2f(0.f, 0.5f);
	}
}