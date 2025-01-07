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
	neighbours = {};
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
						neighbours.push_back(neighbour);
					}
				}
			}
			if (neighbours.size() != targetLength)
			{
				neighbours.push_back(-1);
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
	item->parent = id;
	AddItem(index);
}
void StorageSilo::Update(float dt)
{
	UpdateNeighbours();
	for (int i = 0; i < neighbours.size(); i++)
	{
		if (neighbours[i] == -1)
		{
			continue;
		}
		Conveyor* c = dynamic_cast<Conveyor*>(game->planets[planetID].structures[neighbours[i]]);
		if (c->items[c->direction].size() > 0 && c->progress[c->direction][0] >= 1.f)
		{
			AddItem(c->items[c->direction][0]);
			c->items[c->direction].erase(c->items[c->direction].begin());
			c->progress[c->direction].erase(c->progress[c->direction].begin());
		}
	}
}
void StorageSilo::AddItem(int index)
{
	Item& item = game->planets[planetID].items[index];
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
		itemIDs.push_back(item.typeId);
		itemQuantities.push_back(1);
	}
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
		0 });
	game->planets[planetID].renderObjects.push_back(RenderObject {
		&sprites[1],
		1 });
	for (int i = 0; i < 9; i++)
	{
		if (neighbours[i + 3] != -1)
		{
			game->planets[planetID].renderObjects.push_back(RenderObject {
				&sprites[i + 2],
				1 });
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
			0 });
	game->planets[planetID].renderObjects.push_back(RenderObject {
		&sprites[1],
		1 });
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
	SiloMenu s(this);
	guihandler.AddGUI(&s);
}