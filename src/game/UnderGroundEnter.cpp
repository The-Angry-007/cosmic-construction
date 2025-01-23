#include "UnderGroundEnter.hpp"

#include "Main.hpp"
#include "ResourceHandler.hpp"
#include "utils.hpp"

std::vector<sf::Vector2i> CONVEYOR_OFFSETS = {
	sf::Vector2i(0, -1),
	sf::Vector2i(1, 0),
	sf::Vector2i(0, 1),
	sf::Vector2i(-1, 0),
};

UndergroundEnter::UndergroundEnter(int id, int planetID, int direction)
{
	SetID(id);
	this->planetID = planetID;
	typeID = 10;
	SetDirection(direction);
	tileSize = ResourceHandler::structureSizes[typeID];
	sprite = sf::Sprite();
	ResourceHandler::structureAtlas->SetSprite(sprite, 10, direction);
	gap = 0.2f;
	progress = {};
	items = {};
	speed = 3.f;
	blocksItems = true;
	placedByPlayer = true;
	isConveyor = true;
	length = 0;
	endBelt = -1;
}

void UndergroundEnter::UpdateNeighbours()
{
	// neighbour = -1;
	// int i = direction;
	// sf::Vector2i pos = CONVEYOR_OFFSETS[i] + position;
	// pos += game->planets[planetID].GetChunk(chunkID)->position * CHUNK_SIZE;
	// int index = game->planets[planetID].StructureInPos(pos);
	// if (index != -1)
	// {
	// 	neighbour = index;
	// }
}
void UndergroundEnter::Update(float dt)
{
	ProgressLane(dt);
}

bool UndergroundEnter::ProgressLane(float dt)
{
	bool moved = false;
	for (uint i = 0; i < progress.size(); i++)
	{
		progress[i] += dt * speed;
		if (i == 0)
		{
			if (progress[0] > length)
			{
				if (true)
				{
					//need to either move to end belt or try to add to structure in front of end belt

					// progress[direction].push_back(progress[lane][0] - 1.f);
					// items[direction].push_back(items[lane][0]);
					// items[lane].erase(items[lane].begin());
					// progress[lane].erase(progress[lane].begin());
					// moved = true;
				}
				else
				{
					progress[0] = (float)length;
				}
			}
		}
		else if (i != 0)
		{
			if (progress[i - 1] - progress[i] < gap)
			{
				progress[i] -= dt * speed;
			}
		}
	}
	return moved;
}

void UndergroundEnter::Render()
{
	zindex = -32;
	Planet& p = game->planets[planetID];
	p.renderObjects.push_back(RenderObject {
		&sprite,
		zindex });
}

void UndergroundEnter::SetDirection(int direction)
{
	this->direction = direction;
	ResourceHandler::structureAtlas->SetSprite(sprite, 0, direction);
}

int UndergroundEnter::StructureInFront()
{
	sf::Vector2i pos = position + CONVEYOR_OFFSETS[direction];
	Chunk* chunk = game->planets[planetID].GetChunk(chunkID);
	pos += chunk->position * CHUNK_SIZE;
	return game->planets[planetID].StructureInPos(pos);
}

JSON UndergroundEnter::ToJSON()
{
	JSON j = JSON();
	j.AddAttribute("PositionX", std::to_string(position.x));
	j.AddAttribute("PositionY", std::to_string(position.y));
	j.AddAttribute("TypeID", std::to_string(typeID));
	j.AddAttribute("Direction", std::to_string(direction));
	j.AddAttribute("ID", std::to_string(id));
	j.AddAttribute("ChunkID", std::to_string(chunkID));
	j.AddAttribute("Items", items);
	j.AddAttribute("Progress", progress);

	return j;
}
void UndergroundEnter::FromJSON(JSON j)
{
	sf::Vector2i pos(0, 0);
	pos.x = std::stoi(j.GetValue("PositionX"));
	pos.y = std::stoi(j.GetValue("PositionY"));
	typeID = std::stoi(j.GetValue("TypeID"));

	direction = std::stoi(j.GetValue("Direction"));
	SetID(std::stoi(j.GetValue("ID")));
	chunkID = std::stoi(j.GetValue("ChunkID"));
	pos += game->planets[planetID].GetChunk(chunkID)->position * CHUNK_SIZE;

	ResourceHandler::structureAtlas->SetSprite(sprite, 10, direction);
	SetPosition(pos);
	items = j.GetIntArr("Items");
	progress = j.GetFloatArr("Progress");
}

UndergroundEnter::~UndergroundEnter()
{
	// delete hitbox;
}

void UndergroundEnter::RenderPreview()
{
	int opacity = 100;
	sf::Color col = sf::Color::Green;

	if (!CanBePlaced())
	{
		col = sf::Color(255, 100, 100);
	}
	col.a = opacity;
	sprite.setColor(col);
	Planet& p = game->planets[planetID];
	p.renderObjects.push_back(RenderObject {
		&sprite,
		2000 });
}

void UndergroundEnter::Destroy()
{
	for (int j = 0; j < items.size(); j++)
	{
		Item& item = game->planets[planetID].items[items[j]];
		item.SetParent(-1);
		item.position = (sf::Vector2f)(position + game->planets[planetID].GetChunk(chunkID)->position * CHUNK_SIZE);
		item.position += sf::Vector2f(rand() % 1000, rand() % 1000) / 1000.f;
		item.position.x *= TILE_SIZE.x;
		item.position.y *= TILE_SIZE.y;
		game->planets[planetID].MoveItem(items[j]);
	}
}
bool UndergroundEnter::TryAddItem(int index, int direction, float progress)
{
	if (direction != ((this->direction + 2) % 4))
	{
		return false;
	}
	if (this->progress.size() == 0 || this->progress.back() - progress > gap)
	{
		this->progress.push_back(progress);
		items.push_back(index);
		return true;
	}
	return false;
}
bool UndergroundEnter::TryAddItem(int index, int direction, float progress)
{
	if (direction != ((this->direction + 2) % 4))
	{
		return false;
	}
	if (this->progress.size() == 0 || this->progress.back() - progress > gap)
	{
		return true;
	}
	return false;
}
float UndergroundEnter::Distance(int direction)
{
	if (direction != ((this->direction + 2) % 4))
	{
		return 1.f;
	}
	return progress.back();
}

bool UndergroundEnter::AcceptsItems(int direction)
{
	if (direction == (this->direction + 2) % 4)
	{
		return true;
	}
	return false;
}