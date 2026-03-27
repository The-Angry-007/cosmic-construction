#include "Conveyor.hpp"
#include "../Main.hpp"
#include "../utils.hpp"
#include "ResourceHandler.hpp"
//the offset each value of a structure's direction variable represents
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
	ResourceHandler::structureAtlas->SetSprite(sprite, 0, direction + 4 * upgradeLevel);
	gap = 0.2f;
	//progress is how far along each item is in the 4 queues in the conveyor
	progress = { {}, {}, {}, {} };
	//items stores the ids of the items on each queue in the conveyor
	items = { {}, {}, {}, {} };
	speed = 3.f;
	//the input direction to next add to the main queue (variable name refers to neighbours as this was the old system)
	currentNeighbourIndex = 0;
	blocksItems = false;
	placedByPlayer = true;
	isConveyor = true;
}

void Conveyor::UpdateNeighbours()
{
	//gets the structure in front of the conveyor
	neighbour = -1;
	int i = direction;
	sf::Vector2i pos = CONVEYOR_OFFSETS[i] + position;
	pos += game->planets[planetID].GetChunk(chunkID)->position * CHUNK_SIZE;
	int index = game->planets[planetID].StructureInPos(pos);
	if (index != -1)
	{
		neighbour = index;
	}
}
void Conveyor::Update(float dt)
{
}

void Conveyor::Render()
{
	//render the conveyor sprite
	zindex = -32;
	Planet& p = game->planets[planetID];
	p.renderObjects.push_back(RenderObject {
		&sprite,
		zindex });
	//render all items on the conveyor
	for (uint i = 0; i < 4; i++)
	{
		for (uint j = 0; j < items[i].size(); j++)
		{
			//calculate position of item on conveyor
			sf::Vector2f startPos(0.5f, 0.5f);
			startPos += (sf::Vector2f)CONVEYOR_OFFSETS[i] / 2.f;
			sf::Vector2f endPos(0.5f, 0.5f);
			float prog = progress[i][j];
			//reverse progress if on main queue, since for this queue 0 is the middle of the conveyor, not the edge
			if (i == direction)
				prog = 1 - prog;
			if (prog > 1.f)
			{
				prog = 1.f;
			}
			//lerp between start and end
			sf::Vector2f pos = Lerp(startPos, endPos, prog);
			//set position and render
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
	this->items[dir].push_back(index);
	progress[dir].push_back(0.f);
	//remove item from its chunk
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
	item->SetParent(id);

	return;
}

void Conveyor::SetDirection(int direction)
{
	this->direction = direction;
	ResourceHandler::structureAtlas->SetSprite(sprite, 0, direction + 4 * upgradeLevel);
}
//create JSON object representing conveyor
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
	j.AddAttribute("UpgradeLevel", upgradeLevel);
	for (uint i = 0; i < 4; i++)
	{
		std::string strItems = "";
		std::string strProgress = "";
		//since this code was written before the JSON changes, a list had to be manually created.
		//if this was to be rewritten, i could just call j.AddAttribute("items " + std::to_string(i), items[i]);
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
//load conveyor from JSON object
void Conveyor::FromJSON(JSON j)
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

	ResourceHandler::structureAtlas->SetSprite(sprite, 0, direction + 4 * upgradeLevel);
	SetPosition(pos);

	currentNeighbourIndex = std::stoi(j.GetValue("CurrentNeighbourIndex"));
	for (int i = 0; i < 4; i++)
	{
		//split string into seperate items
		auto items = Split(j.GetValue("items " + std::to_string(i)), ',');
		//skip if empty
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
//draws a red/green version of the conveyor depending on whether it can be placed
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
		2000 });
}
//place items on the ground
void Conveyor::Destroy()
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
//try insert item from another conveyor
bool Conveyor::TryAddItem(int index, int direction, float progress)
{
	//cannot insert into output direction
	if (direction == (this->direction))
	{
		return false;
	}
	if (this->progress[direction].size() == 0 || this->progress[direction].back() - progress > gap)
	{
		this->progress[direction].push_back(progress);
		items[direction].push_back(index);
		return true;
	}
	return false;
}
//same as function above, without actually adding the item
bool Conveyor::CanAddItem(int direction, float progress)
{
	if (direction == (this->direction))
	{
		return false;
	}
	if (this->progress[direction].size() == 0 || this->progress[direction].back() - progress > gap)
	{

		return true;
	}
	return false;
}
//get minimum distance to an item in a given direction
float Conveyor::Distance(int direction)
{
	if (progress[direction].size() == 0)
	{
		return 1.f;
	}
	return progress[direction].back();
}
//check whether items can be added in a certain direction
//any direction is valid except the output direction
bool Conveyor::AcceptsItems(int direction)
{
	if (direction != this->direction)
	{
		return true;
	}
	return false;
}
//move all items forward
void Conveyor::Progress(float dt)
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < progress[i].size(); j++)
		{
			progress[i][j] += dt * speed;
		}
	}
}
//try move item from main queue to next structure and try move items onto main queue
void Conveyor::TryAdd()
{
	if (neighbour != -1 && progress[direction].size() > 0)
	{
		//attempt to add item to another conveyor type object
		Structure* s = game->planets[planetID].structures[neighbour];
		if (s->isConveyor)
		{
			ConveyorType* c = dynamic_cast<ConveyorType*>(s);
			int dir = (direction + 2) % 4;
			if (progress[direction][0] >= 1.f && c->TryAddItem(items[direction][0], dir, progress[direction][0] - 1.f))
			{
				progress[direction].erase(progress[direction].begin());
				items[direction].erase(items[direction].begin());
			}
		}
		else
		//attempt to add item to structure
		{
			if (progress[direction][0] >= 1.f && s->TryAddItem(items[direction][0]))
			{
				items[direction].erase(items[direction].begin());
				progress[direction].erase(progress[direction].begin());
			}
		}
	}
	//try to move item onto main queue
	if (progress[direction].size() == 0 || progress[direction].back() >= gap)
	{
		int numChecked = 0;
		int index = currentNeighbourIndex;
		//cycle through each queue, starting with currentNeighbourIndex + 1 (since currentNeighbourIndex is the last queue an item was taken from)
		while (numChecked < 3)
		{
			numChecked++;
			index = (index + 1) % 4;
			if (index == direction)
			{
				index = (index + 1) % 4;
			}
			if (progress[index].size() > 0 && progress[index][0] >= 1.f)
			{
				progress[direction].push_back(progress[index][0] - 1.f);
				items[direction].push_back(items[index][0]);
				items[index].erase(items[index].begin());
				progress[index].erase(progress[index].begin());
				currentNeighbourIndex = index;
				//if successfully added, end here and set current neighbour index to this direction
				break;
			}
		}
	}
}
//ensure there is a gap between items
void Conveyor::KeepDistance()
{
	for (int i = 0; i < progress[direction].size(); i++)
	{
		if (i == 0)
		{
			//make sure progress is not greater than 1
			if (progress[direction][i] > 1.f)
			{
				progress[direction][i] = 1.f;
			}
			if (neighbour != -1)
			{
				Structure* s = game->planets[planetID].structures[neighbour];
				if (s->isConveyor)
				{
					//make sure front item is sufficiently far from item on next conveyor
					ConveyorType* c = dynamic_cast<ConveyorType*>(s);
					float dist = c->Distance((direction + 2) % 4);
					if (1.f - progress[direction][0] + dist < gap)
					{
						progress[direction][0] = 1.f - (gap - dist);
					}
				}
			}
		}
		else
		{
			//set distance to item in front to gap size if it was less than gap size
			if (progress[direction][i - 1] - progress[direction][i] < gap)
			{
				progress[direction][i] = progress[direction][i - 1] - gap;
				//if progress less than 0, set to 0
				if (progress[direction][i] < 0)
				{
					progress[direction][i] = 0.f;
				}
			}
		}
	}
	//same as bottom part of code above, but for directions other than main direction
	for (int i = 0; i < 4; i++)
	{
		if (direction == i)
		{
			continue;
		}
		if (progress[i].size() > 0 && progress[i][0] > 1.f)
		{
			progress[i][0] = 1.f;
		}
		for (int j = 1; j < progress[i].size(); j++)
		{
			if (progress[i][j - 1] - progress[i][j] < gap)
			{
				progress[i][j] = progress[i][j - 1] - gap;
				if (progress[i][j] < 0)
				{
					progress[i][j] = 0.f;
				}
			}
		}
	}
}