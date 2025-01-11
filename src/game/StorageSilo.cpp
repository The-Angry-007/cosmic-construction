#include "StorageSilo.hpp"
#include "Main.hpp"
#include "ResourceHandler.hpp"
StorageSilo::StorageSilo(int id, int planetID)
{
	SetID(id);
	this->planetID = planetID;
	typeID = 1;
	for (int i = 0; i < 11; i++)
	{
		sf::Sprite s;
		ResourceHandler::structureAtlas->SetSprite(s, typeID, i);
		sprites.push_back(s);
	}
	this->sprite = sf::Sprite();
	tileSize = ResourceHandler::structureSizes[typeID];
	itemIDs = {};
	itemQuantities = {};
	previousOutputs = {};
	for (int i = 0; i < 12; i++)
	{
		previousOutputs.push_back(0);
	}
	items = {};
}
StorageSilo::StorageSilo(int planetID)
{
	this->planetID = planetID;
	typeID = 1;
	for (int i = 0; i < 5; i++)
	{
		sf::Sprite s;
		ResourceHandler::structureAtlas->SetSprite(s, typeID, i);

		sprites.push_back(s);
	}
	this->sprite = sf::Sprite();
	tileSize = ResourceHandler::structureSizes[typeID];
	itemIDs = {};
	itemQuantities = {};
}
void StorageSilo::SetPosition(sf::Vector2i position)
{
	Structure::SetPosition(position);
	for (int i = 0; i < sprites.size(); i++)
	{
		sprites[i].setPosition(this->sprite.getPosition());
	}
	UpdateNeighbours();
}

StorageSilo::~StorageSilo()
{
}

void StorageSilo::UpdateNeighbours()
{
	inputNeighbours = {};
	outputNeighbours = {};
	sf::Vector2i pos = position + (tileSize - sf::Vector2i(1, 1)) / 2;
	pos += game->planets[planetID].GetChunk(chunkID)->position * CHUNK_SIZE;
	int targetLength = 0;
	for (int i = -2; i <= 2; i++)
	{
		for (int j = -2; j <= 2; j++)
		{
			if (abs(j) == 2 && abs(i) == 2)
			{
				continue;
			}
			if (abs(i) < 2 && abs(j) < 2)
			{
				continue;
			}
			targetLength++;
			int direction;
			if (i == 2)
			{
				direction = 0;
			}
			else if (i == -2)
			{
				direction = 2;
			}
			else if (j == -2)
			{
				direction = 1;
			}
			else
			{
				direction = 3;
			}
			int neighbour = game->planets[planetID].StructureInPos(pos + sf::Vector2i(j, i));
			if (neighbour != -1)
			{
				Structure* s = game->planets[planetID].structures[neighbour];
				if (s->typeID == 0)
				{
					Conveyor* c = dynamic_cast<Conveyor*>(s);
					if (c->direction == direction)
					{
						inputNeighbours.push_back(neighbour);
					}
					else if (c->direction == (direction + 2) % 4)
					{
						outputNeighbours.push_back(neighbour);
					}
				}
			}
			if (inputNeighbours.size() != targetLength)
			{
				inputNeighbours.push_back(-1);
			}
			if (outputNeighbours.size() != targetLength)
			{
				outputNeighbours.push_back(-1);
			}
		}
	}
}
void StorageSilo::TryAddGroundItem(int index)
{
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
	// item->parent = id;
	AddItem(index);
}
void StorageSilo::Update(float dt)
{
	UpdateNeighbours();
	for (int i = 0; i < inputNeighbours.size(); i++)
	{
		if (inputNeighbours[i] == -1)
		{
			continue;
		}
		Conveyor* c = dynamic_cast<Conveyor*>(game->planets[planetID].structures[inputNeighbours[i]]);
		if (c->items[c->direction].size() > 0 && c->progress[c->direction][0] >= 1.f)
		{
			AddItem(c->items[c->direction][0]);
			c->items[c->direction].erase(c->items[c->direction].begin());
			c->progress[c->direction].erase(c->progress[c->direction].begin());
		}
	}
	for (int i = 0; i < outputNeighbours.size(); i++)
	{
		if (outputNeighbours[i] != -1)
		{
			Conveyor* c = dynamic_cast<Conveyor*>(game->planets[planetID].structures[outputNeighbours[i]]);
			int dir = (c->direction + 2) % 4;
			if (c->progress[dir].size() == 0 || c->progress[dir][c->progress[dir].size() - 1] > c->gap)
			{
				if (itemIDs.size() > 0)
				{
					previousOutputs[i] %= itemIDs.size();
					//eject item here
					int index = items[items.size() - 1];
					Item& item = game->planets[planetID].items[index];
					item.SetType(itemIDs[previousOutputs[i]]);
					item.parent = outputNeighbours[i];
					c->items[dir].push_back(index);
					c->progress[dir].push_back(0.f);
					itemQuantities[previousOutputs[i]]--;
					if (itemQuantities[previousOutputs[i]] == 0)
					{
						itemQuantities.erase(itemQuantities.begin() + previousOutputs[i]);
						itemIDs.erase(itemIDs.begin() + previousOutputs[i]);
					}
					items.erase(items.end() - 1);
					previousOutputs[i]++;
				}
			}
		}
	}
}
void StorageSilo::AddItem(int index)
{
	Item& item = game->planets[planetID].items[index];
	item.parent = id;
	items.push_back(index);
	bool existing = false;
	for (int i = 0; i < itemIDs.size(); i++)
	{
		if (itemIDs[i] == item.typeId)
		{
			existing = true;
			itemQuantities[i]++;
			break;
		}
	}
	if (!existing)
	{

		if (itemIDs.size() == 0 || item.typeId > itemIDs[itemIDs.size() - 1])
		{
			itemIDs.push_back(item.typeId);
			itemQuantities.push_back(1);
		}
		else
			for (uint i = 0; i < itemIDs.size(); i++)
			{
				if (item.typeId < itemIDs[i])
				{
					itemIDs.insert(itemIDs.begin() + i, item.typeId);
					itemQuantities.insert(itemQuantities.begin() + i, 1);
					break;
				}
			}
	}

	//need to remove item from world - also need to figure out why not rendering?
}
JSON StorageSilo::ToJSON()
{
	return JSON();
}
void StorageSilo::FromJSON(JSON j)
{
}
void StorageSilo::Render()
{
	game->planets[planetID].renderObjects.push_back(RenderObject {
		&sprites[0],
		2 });
	game->planets[planetID].renderObjects.push_back(RenderObject {
		&sprites[1],
		3 });
	for (int i = 0; i < 9; i++)
	{
		if (inputNeighbours[i + 3] != -1 || outputNeighbours[i + 3] != -1)
		{
			int zindex = 4;

			game->planets[planetID].renderObjects.push_back(RenderObject {
				&sprites[i + 2],
				3 });
		}
	}
}

void StorageSilo::RenderPreview()
{
	int opacity = 100;
	sf::Color col = sf::Color::White;
	if (!CanBePlaced())
	{
		col = sf::Color::Red;
	}
	col.a = opacity;
	sprites[0].setColor(col);
	sprites[1].setColor(col);
	game->planets[planetID]
		.renderObjects.push_back(RenderObject {
			&sprites[0],
			100 });
	game->planets[planetID].renderObjects.push_back(RenderObject {
		&sprites[1],
		101 });
}
void StorageSilo::SetVisualPosition(sf::Vector2i pos)
{
	Structure::SetVisualPosition(pos);
	for (uint i = 0; i < sprites.size(); i++)
	{
		sprites[i].setPosition(sprite.getPosition());
	}
}

void StorageSilo::Interact()
{
	std::cout << "interacted with silo" << std::endl;
	guihandler.AddGUI(new SiloMenu(this));
}