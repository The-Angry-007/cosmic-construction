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
	gap = 0.2f;
	progress = { {}, {}, {}, {} };
	items = { {}, {}, {}, {} };
	speed = 1.f;
	currentNeighbourIndex = 0;
	zindex = 0;
}
void Conveyor::UpdateNeighbours()
{
	neighbours = {};
	numNeighbours = 0;
	for (uint i = 0; i < 4; i++)
	{
		sf::Vector2i pos = CONVEYOR_OFFSETS[i] + position;
		pos += game->planets[planetID].GetChunk(chunkID)->position * CHUNK_SIZE;
		int index = game->planets[planetID].StructureInPos(pos);
		if (index == -1)
		{
			neighbours.push_back(-1);
		}
		else
		{
			Structure* s = game->planets[planetID].structures[index];
			if (s->typeID == 0)
			{
				Conveyor* c = dynamic_cast<Conveyor*>(s);
				if (c->direction == (i + 2) % 4)
				{
					neighbours.push_back(index);
					numNeighbours++;
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
}
void Conveyor::Update(float dt)
{
	CollectItems();
	//should ideally only be done when new structures created or destroyed
	UpdateNeighbours();
	//moving items
}
void Conveyor::Render()
{

	Planet& p = game->planets[planetID];
	p.renderObjects.push_back(RenderObject {
		&sprite,
		zindex });
	for (uint i = 0; i < 4; i++)
	{
		for (uint j = 0; j < items[i].size(); j++)
		{
			sf::Vector2f startPos(0.5f, 0.5f);
			startPos += (sf::Vector2f)CONVEYOR_OFFSETS[i] / 2.f;
			sf::Vector2f endPos(0.5f, 0.5f);
			sf::Vector2f pos = Lerp(startPos, endPos, progress[i][j]);
			pos += (sf::Vector2f)position;
			pos += (sf::Vector2f)(game->planets[planetID].GetChunk(chunkID)->position * CHUNK_SIZE);
			pos.x *= TILE_SIZE.x;
			pos.y *= TILE_SIZE.y;
			game->planets[planetID].items[items[i][j]].position = pos;
			game->planets[planetID].items[items[i][j]].Render(&game->planets[planetID]);
		}
	}
}

void Conveyor::CollectItems()
{
	//only add new items if there is room
	int dir = (direction + 2) % 4;
	if (progress[dir].size() > 0 && progress[dir][progress[dir].size() - 1] < gap)
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
		auto tilePos = allItems[items[i]].GetTilePos();
		if (tilePos == position)
		{
			this->items[dir].push_back(items[i]);
			progress[dir].push_back(0.f);
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
