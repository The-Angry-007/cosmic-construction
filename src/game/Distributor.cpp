#include "Distributor.hpp"
#include "Main.hpp"
#include "ResourceHandler.hpp"
#include "utils.hpp"

Distributor::Distributor(int id, int planetID, int direction)
{
	SetID(id);
	this->planetID = planetID;
	this->direction = -1;
	typeID = 9;
	tileSize = ResourceHandler::structureSizes[typeID];
	sprite = sf::Sprite();
	ResourceHandler::structureAtlas->SetSprite(sprite, 9, upgradeLevel);
	gap = 0.2f;
	progress = { {}, {}, {}, {} };
	items = { {}, {}, {}, {} };
	speed = 3.f;
	currentInputIndex = 0;
	currentOutputIndex = 0;
	blocksItems = false;
	placedByPlayer = true;
	isConveyor = true;
}

void Distributor::UpdateNeighbours()
{
	std::vector<sf::Vector2i> offsets = {
		{ 0, -1 },
		{ 1, 0 },
		{ 0, 1 },
		{ -1, 0 }
	};
	std::vector<int> directions = {
		2, 3, 0, 1
	};
	neighbours = {};
	Planet& p = game->planets[planetID];
	sf::Vector2i pos = position + p.GetChunk(chunkID)->position * CHUNK_SIZE;
	for (int i = 0; i < offsets.size(); i++)
	{
		sf::Vector2i newPos = pos + offsets[i];
		int structure = p.StructureInPos(newPos);
		if (structure != -1)
		{
			Structure* s = p.structures[structure];
			if (s->isConveyor && dynamic_cast<ConveyorType*>(s)->AcceptsItems((directions[i])))
			{
				neighbours.push_back(structure);
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
void Distributor::Update(float dt)
{
}

bool Distributor::ProgressLane(int lane, float dt, bool moveToMain)
{
	bool moved = false;
	for (uint i = 0; i < progress[lane].size(); i++)
	{
		progress[lane][i] += dt * speed;
		if (i == 0)
		{
			if (progress[lane][0] >= 1.f)
			{
				if (moveToMain)
				{
					int checked = 0;
					int index = currentOutputIndex;
					bool added = false;
					while (checked < 4)
					{
						if (neighbours[index] != -1 && (progress[index].size() == 0 || progress[index].back() > gap))
						{
							progress[index].push_back(progress[lane][0] - 1.f);
							items[index].push_back(items[lane][0]);
							items[lane].erase(items[lane].begin());
							progress[lane].erase(progress[lane].begin());
							moved = true;
							currentOutputIndex = (index + 1) % 4;
							added = true;
							break;
						}
						else
						{
							index = (index + 1) % 4;
							checked++;
						}
					}
					if (!added)
					{
						progress[lane][0] = 1.f;
					}
				}
				else
				{
					progress[lane][0] = 1.f;
				}
			}
		}
		else if (i != 0)
		{
			if (progress[lane][i - 1] - progress[lane][i] < gap)
			{
				progress[lane][i] -= dt * speed;
			}
		}
	}
	return moved;
}

void Distributor::Render()
{
	zindex = -32;
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
			float prog = progress[i][j];
			if (neighbours[i] != -1)
				prog = 1 - prog;
			if (prog > 1.f)
			{
				prog = 1.f;
			}
			sf::Vector2f pos = Lerp(startPos, endPos, prog);
			pos += (sf::Vector2f)position;
			pos += (sf::Vector2f)(game->planets[planetID].GetChunk(chunkID)->position * CHUNK_SIZE);
			pos.x *= TILE_SIZE.x;
			pos.y *= TILE_SIZE.y;
			game->planets[planetID].items[items[i][j]].position = pos;
			game->planets[planetID].items[items[i][j]].Render(&game->planets[planetID]);
		}
	}
}

void Distributor::TryAddGroundItem(int index)
{
	//only add new items if there is room
	// int dir = (direction + 2) % 4;
	int dir = 0;
	if (progress[dir].size() > 0 && progress[dir][progress[dir].size() - 1] < gap)
	{
		return;
	}
	// if (index == game->toolHandler->draggingItem && game->activePlanet == planetID)
	// {
	// 	return;
	// }
	this->items[dir].push_back(index);
	progress[dir].push_back(0.f);
	Item* item = &game->planets[planetID].items[index];
	Chunk* chunk = game->planets[planetID].GetChunk(item->chunkID);
	for (int i = 0; i < chunk->items.size(); i++)
	{
		if (chunk->items[i] == index)
		{
			chunk->items.erase(chunk->items.begin() + i);
			break;
		}
	}
	game->planets[planetID].items[index].SetParent(id);

	return;
}

void Distributor::SetDirection(int direction)
{
}

int Distributor::StructureInFront()
{
	sf::Vector2i pos = position + CONVEYOR_OFFSETS[direction];
	Chunk* chunk = game->planets[planetID].GetChunk(chunkID);
	pos += chunk->position * CHUNK_SIZE;
	return game->planets[planetID].StructureInPos(pos);
}

JSON Distributor::ToJSON()
{
	JSON j = JSON();
	j.AddAttribute("PositionX", std::to_string(position.x));
	j.AddAttribute("PositionY", std::to_string(position.y));
	j.AddAttribute("TypeID", std::to_string(typeID));
	j.AddAttribute("Direction", std::to_string(direction));
	j.AddAttribute("ID", std::to_string(id));
	j.AddAttribute("ChunkID", std::to_string(chunkID));
	j.AddAttribute("CurrentInputIndex", std::to_string(currentInputIndex));
	j.AddAttribute("CurrentOutputIndex", std::to_string(currentOutputIndex));
	j.AddAttribute("UpgradeLevel", upgradeLevel);
	for (uint i = 0; i < 4; i++)
	{
		std::string strItems = "";
		std::string strProgress = "";
		for (int j = 0; j < items[i].size(); j++)
		{
			strItems += std::to_string(items[i][j]);
			strProgress += std::to_string(progress[i][j]);
			if (j != items[i].size() - 1)
			{
				strItems += ",";
				strProgress += ",";
			}
		}
		j.AddAttribute("items " + std::to_string(i), strItems);
		j.AddAttribute("progress " + std::to_string(i), strProgress);
	}
	return j;
}
void Distributor::FromJSON(JSON j)
{
	sf::Vector2i pos(0, 0);
	pos.x = std::stoi(j.GetValue("PositionX"));
	pos.y = std::stoi(j.GetValue("PositionY"));
	typeID = std::stoi(j.GetValue("TypeID"));
	SetUpgradeLevel(j.GetInt("UpgradeLevel"));
	SetID(std::stoi(j.GetValue("ID")));
	chunkID = std::stoi(j.GetValue("ChunkID"));
	pos += game->planets[planetID].GetChunk(chunkID)->position * CHUNK_SIZE;
	direction = -1;
	ResourceHandler::structureAtlas->SetSprite(sprite, 9, upgradeLevel);
	SetPosition(pos);
	currentInputIndex = j.GetInt("CurrentInputIndex");
	currentOutputIndex = j.GetInt("CurrentOutputIndex");

	for (int i = 0; i < 4; i++)
	{
		auto items = Split(j.GetValue("items " + std::to_string(i)), ',');
		//no items
		if (items.size() == 1 && items[0].length() == 0)
		{
			continue;
		}
		auto progress = Split(j.GetValue("progress " + std::to_string(i)), ',');
		for (int j = 0; j < items.size(); j++)
		{
			this->items[i].push_back(std::stoi(items[j]));
			this->progress[i].push_back(std::stof(progress[j]));
		}
	}
}

Distributor::~Distributor()
{
	// delete hitbox;
}

void Distributor::RenderPreview()
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

void Distributor::Destroy()
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < items[i].size(); j++)
		{
			Item& item = game->planets[planetID].items[items[i][j]];
			item.SetParent(-1);
			item.position = (sf::Vector2f)(position + game->planets[planetID].GetChunk(chunkID)->position * CHUNK_SIZE);
			item.position += sf::Vector2f(rand() % 1000, rand() % 1000) / 1000.f;
			item.position.x *= TILE_SIZE.x;
			item.position.y *= TILE_SIZE.y;
			game->planets[planetID].MoveItem(items[i][j]);
		}
	}
}
bool Distributor::TryAddItem(int index, int direction, float progress)
{
	if (this->progress[direction].size() == 0 || this->progress[direction].back() - progress > gap)
	{
		this->progress[direction].push_back(progress);
		items[direction].push_back(index);
		return true;
	}
	return false;
}
bool Distributor::CanAddItem(int direction, float progress)
{
	if (this->progress[direction].size() == 0 || this->progress[direction].back() - progress > gap)
	{
		return true;
	}
	return false;
}
float Distributor::Distance(int direction)
{
	if (progress[direction].size() == 0)
	{
		return 1.f;
	}
	return progress[direction].back();
}

bool Distributor::AcceptsItems(int direction)
{
	return true;
}

void Distributor::Progress(float dt)
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < progress[i].size(); j++)
		{
			progress[i][j] += dt * speed;
		}
	}
}

void Distributor::TryAdd()
{
	int numChecked = 0;
	int index = currentInputIndex;
	while (numChecked < 4)
	{
		numChecked++;
		index = (index + 1) % 4;
		if (neighbours[index] != -1)
		{
			if (progress[index].size() > 0)
			{
				Structure* s = game->planets[planetID].structures[neighbours[index]];
				if (s->isConveyor)
				{
					ConveyorType* c = dynamic_cast<ConveyorType*>(s);
					int dir = (index + 2) % 4;
					if (progress[index][0] >= 1.f && c->TryAddItem(items[index][0], dir, progress[index][0] - 1.f))
					{
						progress[index].erase(progress[index].begin());
						items[index].erase(items[index].begin());
					}
				}
				else
				{
					if (progress[index][0] >= 1.f && s->TryAddItem(items[index][0]))
					{
						items[index].erase(items[index].begin());
						progress[index].erase(progress[index].begin());
					}
				}
			}
		}
		else
		{
			if (progress[index].size() > 0 && progress[index][0] >= 1.f)
			{
				int numChecked = 0;
				int index2 = currentOutputIndex;
				while (numChecked < 4)
				{
					numChecked++;
					index2 = (index2 + 1) % 4;
					if (neighbours[index2] != -1)
					{
						if (progress[index2].size() == 0 || progress[index2].back() > gap)
						{
							progress[index2].push_back(progress[index][0] - 1.f);
							items[index2].push_back(items[index][0]);
							progress[index].erase(progress[index].begin());
							items[index].erase(items[index].begin());
							currentOutputIndex = index2;
							break;
						}
					}
				}
			}
		}
	}
}

void Distributor::KeepDistance()
{
	for (int j = 0; j < 4; j++)
	{
		if (neighbours[j] != -1)
		{
			int direction = j;
			for (int i = 0; i < progress[direction].size(); i++)
			{
				if (i == 0)
				{
					if (progress[direction][i] > 1.f)
					{
						progress[direction][i] = 1.f;
					}
					Structure* s = game->planets[planetID].structures[neighbours[direction]];
					if (s->isConveyor)
					{
						ConveyorType* c = dynamic_cast<ConveyorType*>(s);
						float dist = c->Distance((direction + 2) % 4);
						if (1.f - progress[direction][0] + dist < gap)
						{
							progress[direction][0] = 1.f - (gap - dist);
						}
					}
				}
				else
				{
					if (progress[direction][i - 1] - progress[direction][i] < gap)
					{
						progress[direction][i] = progress[direction][i - 1] - gap;
						if (progress[direction][i] < 0)
						{
							progress[direction][i] = 0.f;
						}
					}
				}
			}
		}
		else
		{
			for (int k = 0; k < progress[j].size(); k++)
			{
				if (k == 0)
				{
					if (progress[j][k] > 1.f)
					{
						progress[j][k] = 1.f;
					}
				}
				else
				{

					if (progress[j][k - 1] - progress[j][k] < gap)
					{
						progress[j][k] = progress[j][k - 1] - gap;
						if (progress[j][k] < 0)
						{
							progress[j][k] = 0.f;
						}
					}
				}
			}
		}
	}
}