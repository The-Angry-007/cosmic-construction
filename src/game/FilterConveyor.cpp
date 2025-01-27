#include "FilterConveyor.hpp"
#include "Main.hpp"
#include "ResourceHandler.hpp"
#include "utils.hpp"

FilterConveyor::FilterConveyor(int id, int planetID, int direction)
{
	SetID(id);
	this->planetID = planetID;
	typeID = 17;
	SetDirection(direction);
	tileSize = ResourceHandler::structureSizes[typeID];
	sprite = sf::Sprite();
	ResourceHandler::structureAtlas->SetSprite(sprite, 17, direction);
	overlaySprite = sf::Sprite();
	ResourceHandler::structureAtlas->SetSprite(overlaySprite, 17, 8);

	gap = 0.2f;
	progress = { {}, {}, {}, {} };
	items = { {}, {}, {}, {} };
	speed = 3.f;
	blocksItems = false;
	placedByPlayer = true;
	isConveyor = true;
	filterItem = -1;
}

void FilterConveyor::UpdateNeighbours()
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
			// if (s->isConveyor && dynamic_cast<ConveyorType*>(s)->AcceptsItems((directions[i])))
			// {
			// 	neighbours.push_back(structure);
			// }
			// else
			// {
			// }
			neighbours.push_back(structure);
		}
		else
		{
			neighbours.push_back(-1);
		}
	}
}
void FilterConveyor::Update(float dt)
{
}

void FilterConveyor::Render()
{
	zindex = -32;
	Planet& p = game->planets[planetID];
	p.renderObjects.push_back(RenderObject {
		&sprite,
		zindex });
	p.renderObjects.push_back(RenderObject {
		&overlaySprite,
		99 });
	if (filterItem != -1)
	{
		Item& item = game->planets[planetID].items[filterItem];
		item.zindex = 100;
		sf::Vector2i tilepos = position + game->planets[planetID].GetChunk(chunkID)->position * CHUNK_SIZE;
		sf::Vector2f pos((tilepos.x + 0.5f) * TILE_SIZE.x, (tilepos.y + 0.5f) * TILE_SIZE.y);
		item.position = pos;
		item.Render(&game->planets[planetID]);
	}
	for (uint i = 0; i < 4; i++)
	{
		for (uint j = 0; j < items[i].size(); j++)
		{
			sf::Vector2f startPos(0.5f, 0.5f);
			startPos += (sf::Vector2f)CONVEYOR_OFFSETS[i] / 2.f;
			sf::Vector2f endPos(0.5f, 0.5f);
			float prog = progress[i][j];
			if (i != (direction + 2) % 4)
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

void FilterConveyor::TryAddGroundItem(int index)
{
	//only add new items if there is room
	int dir = (direction + 2) % 4;
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
	item->SetParent(id);

	return;
}
void FilterConveyor::SetPosition(sf::Vector2i position)
{
	Structure::SetPosition(position);
	overlaySprite.setPosition(sprite.getPosition());
}
void FilterConveyor::SetDirection(int direction)
{
	this->direction = direction;
	ResourceHandler::structureAtlas->SetSprite(sprite, 17, direction + 4 * isFlipped);
}
void FilterConveyor::SetFlipped(bool flipped)
{
	this->isFlipped = flipped;
	ResourceHandler::structureAtlas->SetSprite(sprite, 17, direction + 4 * isFlipped);
}
JSON FilterConveyor::ToJSON()
{
	JSON j = JSON();
	j.AddAttribute("PositionX", std::to_string(position.x));
	j.AddAttribute("PositionY", std::to_string(position.y));
	j.AddAttribute("TypeID", std::to_string(typeID));
	j.AddAttribute("Direction", std::to_string(direction));
	j.AddAttribute("ID", std::to_string(id));
	j.AddAttribute("ChunkID", std::to_string(chunkID));
	j.AddAttribute("FilterItem", filterItem);
	j.AddAttribute("IsFlipped", isFlipped);
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
void FilterConveyor::FromJSON(JSON j)
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
	isFlipped = j.GetInt("IsFlipped");

	ResourceHandler::structureAtlas->SetSprite(sprite, 17, direction + 4 * isFlipped);
	SetPosition(pos);
	filterItem = j.GetInt("FilterItem");

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

FilterConveyor::~FilterConveyor()
{
	// delete hitbox;
}

void FilterConveyor::RenderPreview()
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

void FilterConveyor::Destroy()
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
	if (filterItem != -1)
	{
		Item& item = game->planets[planetID].items[filterItem];
		item.zindex = 1;
		item.SetParent(-1);
		item.position = (sf::Vector2f)(position + game->planets[planetID].GetChunk(chunkID)->position * CHUNK_SIZE);
		item.position += sf::Vector2f(rand() % 1000, rand() % 1000) / 1000.f;
		item.position.x *= TILE_SIZE.x;
		item.position.y *= TILE_SIZE.y;
		game->planets[planetID].MoveItem(item.id);
	}
}
bool FilterConveyor::TryAddItem(int index, int direction, float progress)
{
	if (direction != (this->direction + 2) % 4)
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
bool FilterConveyor::CanAddItem(int direction, float progress)
{
	if (direction != (this->direction + 2) % 4)
	{
		return false;
	}

	if (this->progress[direction].size() == 0 || this->progress[direction].back() - progress > gap)
	{

		return true;
	}
	return false;
}
float FilterConveyor::Distance(int direction)
{
	if (progress[direction].size() == 0)
	{
		return 1.f;
	}
	return progress[direction].back();
}

bool FilterConveyor::AcceptsItems(int direction)
{
	return (direction == (this->direction + 2) % 4);
}

void FilterConveyor::Progress(float dt)
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < progress[i].size(); j++)
		{
			progress[i][j] += dt * speed;
		}
	}
}

void FilterConveyor::TryAdd()
{
	int numChecked = 0;
	int index = 0;
	while (numChecked < 4)
	{
		numChecked++;
		index = (index + 1) % 4;
		if (index == (direction + 2) % 4)
		{
			continue;
		}
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
		// if (progress[index].size() > 0 && progress[index][0] >= 1.f)
		// {
		// 	int numChecked = 0;
		// 	int index2 = currentOutputIndex;
		// 	while (numChecked < 4)
		// 	{
		// 		numChecked++;
		// 		index2 = (index2 + 1) % 4;
		// 		if (neighbours[index2] != -1)
		// 		{
		// 			if (progress[index2].size() == 0 || progress[index2].back() > gap)
		// 			{
		// 				progress[index2].push_back(progress[index][0] - 1.f);
		// 				items[index2].push_back(items[index][0]);
		// 				progress[index].erase(progress[index].begin());
		// 				items[index].erase(items[index].begin());
		// 				currentOutputIndex = index2;
		// 				break;
		// 			}
		// 		}
		// 	}
		// }
	}
	int dir = (direction + 2) % 4;
	if (progress[dir].size() > 0 && progress[dir][0] > 1.f)
	{
		int outputDir = direction;
		if (filterItem != -1)
		{
			auto& items = game->planets[planetID].items;
			int filterType = items[filterItem].typeId;
			if (filterType == items[this->items[dir][0]].typeId)
			{
				if (this->isFlipped)
				{
					outputDir = (direction + 1) % 4;
				}
				else
				{
					outputDir = (direction + 3) % 4;
				}
			}
		}
		else
		{
			filterItem = items[dir][0];
			progress[dir].erase(progress[dir].begin());
			items[dir].erase(items[dir].begin());
			return;
		}
		if (progress[outputDir].size() == 0 || progress[outputDir].back() > gap)
		{
			progress[outputDir].push_back(progress[dir][0] - 1.f);
			items[outputDir].push_back(items[dir][0]);
			items[dir].erase(items[dir].begin());
			progress[dir].erase(progress[dir].begin());
		}
	}
}

void FilterConveyor::KeepDistance()
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