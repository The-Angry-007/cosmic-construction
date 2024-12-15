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
	zindex = 0;
}
void Conveyor::UpdateNeighbours()
{
	neighbours = {};
	for (int x = -1; x <= 1; x++)
	{
		for (int y = -1; y <= 1; y++)
		{
			if (x == 0 && y == 0)
			{
				continue;
			}
			if (x != 0 && y != 0)
			{
				continue;
			}
			sf::Vector2i pos = position + sf::Vector2i(x, y);

			pos += game->planets[planetID].GetChunk(chunkID)->position * CHUNK_SIZE;
			int index = game->planets[planetID].StructureInPos(pos);
			if (index != -1)
			{
				if (game->planets[planetID].structures[index]->typeID == 0)
				{
					Conveyor* c = dynamic_cast<Conveyor*>(game->planets[planetID].structures[index]);
					sf::Vector2i p1 = position + game->planets[planetID].GetChunk(chunkID)->position * CHUNK_SIZE;
					sf::Vector2i p2 = c->position + CONVEYOR_OFFSETS[c->direction] + game->planets[c->planetID].GetChunk(c->chunkID)->position * CHUNK_SIZE;
					if (p1 == p2)
					{
						neighbours.push_back(index);
					}
				}
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
	for (uint i = 0; i < positions.size(); i++)
	{
		bool offCentre = false;
		if (direction == 0 || direction == 2)
		{
			if (positions[i].x != 0.5f)
			{
				offCentre = true;
				if (positions[i].x < 0.5f)
				{
					if (i > 0)
					{
						float dx = positions[i].x - positions[i - 1].x;
						float dy = positions[i].y - positions[i - 1].y;
						if (dx * dx + dy * dy > gap * gap)
						{
							positions[i].x += dt * speed;
							if (positions[i].x > 0.5f)
							{
								positions[i].x = 0.5f;
							}
						}
					}
					else
					{
						positions[i].x += dt * speed;
						if (positions[i].x > 0.5f)
						{
							positions[i].x = 0.5f;
						}
					}
				}
				else
				{
					if (i > 0)
					{
						float dx = positions[i].x - positions[i - 1].x;
						float dy = positions[i].y - positions[i - 1].y;
						if (dx * dx + dy * dy > gap * gap)
						{
							positions[i].x -= dt * speed;
							if (positions[i].x < 0.5f)
							{
								positions[i].x = 0.5f;
							}
						}
					}
					else
					{
						positions[i].x -= dt * speed;
						if (positions[i].x < 0.5f)
						{
							positions[i].x = 0.5f;
						}
					}
				}
			}
		}
		else
		{
			if (positions[i].y != 0.5f)
			{
				offCentre = true;
				if (positions[i].y < 0.5f)
				{
					if (i > 0)
					{
						bool dist = false;
						if ((direction == 0 || direction == 2) && abs(positions[i - 1].y - positions[i].y) > gap)
							dist = true;
						if ((direction == 1 || direction == 3) && abs(positions[i - 1].x - positions[i].x) > gap)
							dist = true;
						if (dist)
						{
							positions[i].y += dt * speed;
							if (positions[i].y > 0.5f)
							{
								positions[i].y = 0.5f;
							}
						}
					}
					else
					{
						positions[i].y += dt * speed;
						if (positions[i].y > 0.5f)
						{
							positions[i].y = 0.5f;
						}
					}
				}
				else
				{
					if (i > 0)
					{
						bool dist = false;
						if ((direction == 0 || direction == 2) && abs(positions[i - 1].y - positions[i].y) > gap)
							dist = true;
						if ((direction == 1 || direction == 3) && abs(positions[i - 1].x - positions[i].x) > gap)
							dist = true;
						if (dist)
						{
							positions[i].y -= dt * speed;
							if (positions[i].y < 0.5f)
							{
								positions[i].y = 0.5f;
							}
						}
					}
					else
					{
						positions[i].y -= dt * speed;
						if (positions[i].y < 0.5f)
						{
							positions[i].y = 0.5f;
						}
					}
				}
			}
		}
		if (offCentre)
		{
			continue;
		}
		if (i > 0)
		{
			bool dist = false;
			if ((direction == 0 || direction == 2) && abs(positions[i - 1].y - positions[i].y) > gap)
				dist = true;
			if ((direction == 1 || direction == 3) && abs(positions[i - 1].x - positions[i].x) > gap)
				dist = true;
			if (dist)
			{
				positions[i] += (sf::Vector2f)CONVEYOR_OFFSETS[direction] * dt * speed;
			}
		}
		else
		{
			if (positions[i].x < 1.f && positions[i].x > 0.f && positions[i].y < 1.f && positions[i].y > 0.f)
			{
				positions[i] += (sf::Vector2f)CONVEYOR_OFFSETS[direction] * dt * speed;
			}

			// positions[i].x = clamp(positions[i].x, 0.f, 1.f);
			// positions[i].y = clamp(positions[i].y, 0.f, 1.f);
		}
	}
	//get items from neighbours and attempt to add to this one
	int checkedNeighbours = 0;
	int startIndex = currentNeighbourIndex;
	bool transferred = false;
	while (checkedNeighbours < neighbours.size())
	{
		Conveyor* neighbour = dynamic_cast<Conveyor*>(game->planets[planetID].structures[neighbours[currentNeighbourIndex]]);
		if (neighbour->positions.size() > 0)
		{
			bool ready = false;
			float extra;
			if (neighbour->direction == 0 && neighbour->positions[0].y < 0.f)
			{
				extra = -neighbour->positions[0].y;
				ready = true;
			}
			else if (neighbour->direction == 1 && neighbour->positions[0].x > 1.f)
			{
				extra = neighbour->positions[0].x - 1;
				ready = true;
			}
			else if (neighbour->direction == 2 && neighbour->positions[0].y > 1.f)
			{
				extra = neighbour->positions[0].y - 1;
				ready = true;
			}
			else if (neighbour->direction == 3 && neighbour->positions[0].x < 0.f)
			{
				extra = -neighbour->positions[0].x;
				ready = true;
			}
			if (ready)
			{
				sf::Vector2f pos(0.5f, 0.5f);
				pos -= (sf::Vector2f)CONVEYOR_OFFSETS[neighbour->direction] / 2.f;
				pos += (sf::Vector2f)CONVEYOR_OFFSETS[neighbour->direction] * extra;
				int closestPos = -1;
				float dist = 1000000.f;
				for (int i = 0; i < positions.size(); i++)
				{
					float dx = pos.x - positions[i].x;
					float dy = pos.y - positions[i].y;
					float d = dx * dx + dy * dy;
					if (d < dist)
					{
						closestPos = i;
						dist = d;
					}
				}
				if (closestPos == -1 || dist > gap * gap)
				{
					//add item
					int index = positions.size();
					for (uint i = 0; i < positions.size(); i++)
					{
						if (direction == 0 && positions[i].y > pos.y)
						{
							index = i;
							break;
						}
						else if (direction == 1 && positions[i].x < pos.x)
						{
							index = i;
							break;
						}
						else if (direction == 2 && positions[i].y < pos.y)
						{
							index = i;
							break;
						}
						else if (direction == 3 && positions[i].x > pos.x)
						{
							index = i;
							break;
						}
					}
					positions.insert(positions.begin() + index, pos);
					items.insert(items.begin() + index, neighbour->items[0]);
					neighbour->items.erase(neighbour->items.begin());
					neighbour->positions.erase(neighbour->positions.begin());
					transferred = true;
					break;
				}
			}
		}
		currentNeighbourIndex = (currentNeighbourIndex + 1) % neighbours.size();
		checkedNeighbours++;
	}
	if (transferred)
	{
		currentNeighbourIndex = (startIndex + 1) % neighbours.size();
	}
}
void Conveyor::Render()
{

	Planet& p = game->planets[planetID];
	p.renderObjects.push_back(RenderObject {
		&sprite,
		zindex });

	for (uint i = 0; i < items.size(); i++)
	{
		sf::Vector2f pos = positions[i];
		pos += (sf::Vector2f)position;
		p.items[items[i]].position = p.worldPos(pos, chunkID);
		p.items[items[i]].Render(&game->planets[planetID]);
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
		auto tilePos = allItems[items[i]].GetTilePos();
		if (tilePos == position)
		{
			sf::Vector2f pos = allItems[items[i]].position;
			pos.x /= TILE_SIZE.x;
			pos.y /= TILE_SIZE.y;
			pos.x -= (int)pos.x;
			pos.y -= (int)pos.y;
			if (pos.x < 0)
				pos.x = (1 + pos.x);
			if (pos.y < 0)
				pos.y = (1 + pos.y);
			positions.push_back(pos);
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
