#include "UnderGroundEnter.hpp"

#include "Main.hpp"
#include "ResourceHandler.hpp"
#include "utils.hpp"

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
	speed = 3.f;
	progress = {};
	items = {};
	blocksItems = true;
	placedByPlayer = true;
	isConveyor = true;
	length = 0;
	maxLength = 5;
	endBelt = -1;
}

void UndergroundEnter::UpdateNeighbours()
{
	if (isFlipped)
	{
		return;
	}
	Planet& p = game->planets[planetID];
	endBelt = -1;
	length = 0;
	sf::Vector2i pos = position + p.GetChunk(chunkID)->position * CHUNK_SIZE;
	for (int i = 1; i <= maxLength; i++)
	{
		sf::Vector2i offset = CONVEYOR_OFFSETS[direction] * i;
		sf::Vector2i tilePos = pos + offset;
		int structure = p.StructureInPos(tilePos);
		if (structure != -1)
		{
			Structure* s = p.structures[structure];
			if (s->typeID == 10 && s->direction == direction)
			{
				endBelt = structure;
				endBeltPos = tilePos;
				length = (i + 1) * 2.f;
				break;
			}
		}
	}
	if (endBelt != -1)
	{
		neighbour = p.StructureInPos(endBeltPos + CONVEYOR_OFFSETS[direction]);
	}
	else
	{
		neighbour = -1;
	}
}
void UndergroundEnter::Update(float dt)
{
	// ProgressLane(dt);
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
	ResourceHandler::structureAtlas->SetSprite(sprite, 10, direction + 4 * upgradeLevel);
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
	j.AddAttribute("UpgradeLevel", upgradeLevel);
	j.AddAttribute("IsFlipped", isFlipped);

	return j;
}
void UndergroundEnter::FromJSON(JSON j)
{
	sf::Vector2i pos(0, 0);
	pos.x = std::stoi(j.GetValue("PositionX"));
	pos.y = std::stoi(j.GetValue("PositionY"));
	typeID = std::stoi(j.GetValue("TypeID"));
	SetUpgradeLevel(j.GetInt("UpgradeLevel"));

	direction = std::stoi(j.GetValue("Direction"));
	SetID(std::stoi(j.GetValue("ID")));
	chunkID = std::stoi(j.GetValue("ChunkID"));
	pos += game->planets[planetID].GetChunk(chunkID)->position * CHUNK_SIZE;
	SetFlipped(j.GetInt("IsFlipped"));
	ResourceHandler::structureAtlas->SetSprite(sprite, 10, direction);
	SetPosition(pos);
	items = j.GetIntArr("Items");
	progress = j.GetFloatArr("Progress");
}

void UndergroundEnter::SetFlipped(bool flipped)
{
	if (flipped == isFlipped)
	{
		return;
	}
	if (!flipped)
	{
		progress = {};
		for (int i = 0; i < items.size(); i++)
		{
			game->planets[planetID].RemoveItem(items[i]);
		}
		items = {};
	}
	isFlipped = flipped;
	ResourceHandler::structureAtlas->SetSprite(sprite, 10, direction + 4 * isFlipped);
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
	if (isFlipped)
	{
		return;
	}
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
	if (isFlipped)
	{
		return false;
	}
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
bool UndergroundEnter::CanAddItem(int direction, float progress)
{
	if (isFlipped)
	{
		return false;
	}
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
	if (isFlipped)
	{
		return 1.f;
	}
	if (direction != ((this->direction + 2) % 4) || progress.size() == 0)
	{
		return 1.f;
	}
	return progress.back();
}

bool UndergroundEnter::AcceptsItems(int direction)
{
	if (isFlipped)
	{
		return false;
	}
	if (direction == (this->direction + 2) % 4)
	{
		return true;
	}
	return false;
}

void UndergroundEnter::Progress(float dt)
{
	if (isFlipped)
	{
		return;
	}
	for (int i = 0; i < progress.size(); i++)
	{
		progress[i] += dt * speed;
	}
}
void UndergroundEnter::TryAdd()
{
	if (isFlipped)
	{
		return;
	}
	if (neighbour != -1 && progress.size() > 0 && progress[0] >= length)
	{
		Structure* s = game->planets[planetID].structures[neighbour];
		if (s->isConveyor)
		{
			ConveyorType* c = dynamic_cast<ConveyorType*>(s);
			if (c->TryAddItem(items[0], (direction + 2) % 4, 0.f))
			{
				progress.erase(progress.begin());
				items.erase(items.begin());
			}
		}
		else
		{
			if (s->TryAddItem(items[0]))
			{
				progress.erase(progress.begin());
				items.erase(items.begin());
			}
		}
	}
}

void UndergroundEnter::KeepDistance()
{
	if (isFlipped)
	{
		return;
	}
	for (int i = 0; i < progress.size(); i++)
	{
		if (i == 0)
		{
			if (progress[i] > length)
			{
				progress[i] = (float)length;
			}
		}
		else
		{
			if (progress[i - 1] - progress[i] < gap)
			{
				progress[i] = progress[i - 1] - gap;
				if (progress[i] < 0)
				{
					progress[i] = 0.f;
				}
			}
		}
	}
}