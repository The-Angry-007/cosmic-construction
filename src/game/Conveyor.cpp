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
	sprite = sf::Sprite();
	ResourceHandler::structureAtlas->SetSprite(sprite, 0, direction);
	gap = 0.2f;
	progress = { {}, {}, {}, {} };
	items = { {}, {}, {}, {} };
	speed = 3.f;
	currentNeighbourIndex = 0;
	blocksItems = false;
}
Conveyor::Conveyor(int planetID)
{
	this->planetID = planetID;
	blocksItems = false;
	speed = 3.f;
	gap = 0.2f;
}
void Conveyor::UpdateNeighbours()
{
	neighbours = {};
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
	//should ideally only be done when new structures created or destroyed
	UpdateNeighbours();
	//moving items
	int numChecked = 0;
	int index = currentNeighbourIndex;
	while (numChecked < 3)
	{
		numChecked++;
		if (index == direction)
		{
			index = (index + 1) % 4;
			numChecked--;
			continue;
		}
		if (progress[index].size() > 0)
		{
			ProgressLane(index, dt);
			break;
		}
		index = (index + 1) % 4;
	}
	for (uint i = 0; i < items[direction].size(); i++)
	{
		if (i == 0)
		{
			if (progress[direction][i] > 1.f)
			{
				progress[direction][i] = 1.f;
			}
			progress[direction][i] += speed * dt;

			if (neighbours[direction] != -1)
			{
				Structure* s = game->planets[planetID].structures[neighbours[direction]];
				Conveyor* c = dynamic_cast<Conveyor*>(s);
				int dir = (direction + 2) % 4;
				if (c->progress[dir].size() > 0)
				{
					float prog = c->progress[dir][c->progress[dir].size() - 1];
					if (prog + (1 - progress[direction][i]) < gap)
					{
						progress[direction][i] -= speed * dt;
					}
				}
			}
		}
		else
		{
			if (progress[direction][i - 1] - progress[direction][i] > gap)
			{
				progress[direction][i] += speed * dt;
			}
		}
	}
	//get items from neighbouring conveyors
	for (uint i = 0; i < 4; i++)
	{
		if (i == direction)
		{
			continue;
		}
		if (neighbours[i] == -1)
		{
			continue;
		}
		if (progress[i].size() == 0 || progress[i][progress[i].size() - 1] > gap)
		{
			Structure* s = game->planets[planetID].structures[neighbours[i]];
			Conveyor* c = dynamic_cast<Conveyor*>(s);
			if (c->items[c->direction].size() > 0)
			{
				if (c->progress[c->direction][0] >= 1.f)
				{
					items[i].push_back(c->items[c->direction][0]);
					progress[i].push_back(c->progress[c->direction][0] - 1.f);
					c->items[c->direction].erase(c->items[c->direction].begin());
					c->progress[c->direction].erase(c->progress[c->direction].begin());
				}
			}
		}
	}
}

void Conveyor::ProgressLane(int lane, float dt)
{
	for (uint i = 0; i < progress[lane].size(); i++)
	{
		progress[lane][i] += dt * speed;
		if (i == 0)
		{
			if (progress[direction].size() > 0)
			{
				float prog = progress[direction][progress[direction].size() - 1];
				if ((1 - progress[lane][i]) + prog < gap)
				{
					progress[lane][i] -= dt * speed;
				}
			}
			if (progress[lane][0] > 1.f)
			{
				progress[direction].push_back(progress[lane][0] - 1.f);
				items[direction].push_back(items[lane][0]);
				items[lane].erase(items[lane].begin());
				progress[lane].erase(progress[lane].begin());
				//cycle current neighbour index
				currentNeighbourIndex = (lane + 1) % 4;
				if (currentNeighbourIndex == direction)
				{
					currentNeighbourIndex = (currentNeighbourIndex + 1) % 4;
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
}

void Conveyor::Render()
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
			if (i == direction)
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

void Conveyor::TryAddGroundItem(int index)
{
	//only add new items if there is room
	int dir = (direction + 2) % 4;
	if (progress[dir].size() > 0 && progress[dir][progress[dir].size() - 1] < gap)
	{
		return;
	}
	if (index == game->toolHandler->draggingItem && game->activePlanet == planetID)
	{
		return;
	}
	this->items[dir].push_back(index);
	progress[dir].push_back(0.f);
	game->planets[planetID].items[index].SetParent(id);
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
	return;
}

void Conveyor::SetDirection(int direction)
{
	this->direction = direction;
	ResourceHandler::structureAtlas->SetSprite(sprite, 0, direction);
}

int Conveyor::StructureInFront()
{
	sf::Vector2i pos = position + CONVEYOR_OFFSETS[direction];
	Chunk* chunk = game->planets[planetID].GetChunk(chunkID);
	pos += chunk->position * CHUNK_SIZE;
	return game->planets[planetID].StructureInPos(pos);
}

JSON Conveyor::ToJSON()
{
	JSON j = JSON();
	j.AddAttribute("PositionX", std::to_string(position.x));
	j.AddAttribute("PositionY", std::to_string(position.y));
	j.AddAttribute("TypeID", std::to_string(typeID));
	j.AddAttribute("Direction", std::to_string(direction));
	j.AddAttribute("ID", std::to_string(id));
	j.AddAttribute("ChunkID", std::to_string(chunkID));
	j.AddAttribute("CurrentNeighbourIndex", std::to_string(currentNeighbourIndex));
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
void Conveyor::FromJSON(JSON j)
{
	sf::Vector2i pos;
	pos.x = std::stoi(j.GetValue("PositionX"));
	pos.y = std::stoi(j.GetValue("PositionY"));
	typeID = std::stoi(j.GetValue("TypeID"));
	direction = std::stoi(j.GetValue("Direction"));
	id = std::stoi(j.GetValue("ID"));
	chunkID = std::stoi(j.GetValue("ChunkID"));
	pos += game->planets[planetID].GetChunk(chunkID)->position * CHUNK_SIZE;

	tileSize = ResourceHandler::structureSizes[typeID];
	sprite = sf::Sprite();
	ResourceHandler::structureAtlas->SetSprite(sprite, 0, direction);
	SetPosition(pos);

	progress = { {}, {}, {}, {} };
	items = { {}, {}, {}, {} };

	currentNeighbourIndex = std::stoi(j.GetValue("CurrentNeighbourIndex"));
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

Conveyor::~Conveyor()
{
	// delete hitbox;
}

void Conveyor::RenderPreview()
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
		zindex + 200 });
}