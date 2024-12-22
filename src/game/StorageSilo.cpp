#include "StorageSilo.hpp"
#include "Main.hpp"
#include "ResourceHandler.hpp"
StorageSilo::StorageSilo(int id, int planetID)
{
	SetID(id);
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
StorageSilo::StorageSilo(int planetID)
{
	this->planetID = planetID;
	typeID = 1;
	for (int i = 0; i < 5; i++)
	{
		sf::Sprite s;
		ResourceHandler::structureAtlas->SetSprite(s, typeID, i);
		// if (i >= 2)
		// {
		// 	s.setPosition(s.getPosition() + sf::Vector2f(1.f, 1.f));
		// }
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

void StorageSilo::UpdateNeighbours()
{
	neighbours = {};
	sf::Vector2i pos = position + (tileSize - sf::Vector2i(1, 1)) / 2;
	pos += game->planets[planetID].GetChunk(chunkID)->position * CHUNK_SIZE;
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
			neighbours.push_back(game->planets[planetID].StructureInPos(pos + sf::Vector2i(j, i)));
		}
	}
}
void StorageSilo::Update(float dt)
{
	UpdateNeighbours();
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
	for (int i = 0; i < tileSize.x; i++)
	{
		if (neighbours[neighbours.size() - 1 - i] != -1)
		{
			Structure* s = game->planets[planetID].structures[neighbours[neighbours.size() - 1 - i]];
			if (s->typeID == 0)
			{
				Conveyor* c = dynamic_cast<Conveyor*>(s);
				if (c->direction == 0)
				{
					game->planets[planetID].renderObjects.push_back(RenderObject {
						&sprites[sprites.size() - i - 1],
						1 });
				}
			}
		}
	}
}