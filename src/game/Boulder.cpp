#include "Boulder.hpp"
#include "Main.hpp"
#include "ResourceHandler.hpp"
Boulder::Boulder(int id, int planetID)
{
	SetID(id);
	this->planetID = planetID;
	typeID = 5;
	health = 5;
	tileSize = ResourceHandler::structureSizes[typeID];
	sprite = sf::Sprite();
	ResourceHandler::structureAtlas->SetSprite(sprite, typeID, 0);
	blocksItems = true;
	placedByPlayer = false;
	chunkID = -1;
}

Boulder ::~Boulder()
{}

void Boulder::Destroy()
{
	int numItems = 3;
	Planet& p = game->planets[planetID];
	for (int i = 0; i < numItems; i++)
	{
		sf::Vector2f pos = (sf::Vector2f)position;
		pos += (sf::Vector2f)(p.GetChunk(chunkID)->position * CHUNK_SIZE);
		pos += sf::Vector2f(rand() % 1000, rand() % 1000) / 1000.f;
		pos.x *= TILE_SIZE.x;
		pos.y *= TILE_SIZE.y;
		p.items.push_back(Item(pos, -1, 1));
		p.items.back().SetParent(-1);
		p.MoveItem(p.items.size() - 1);
	}
}

void Boulder::FromJSON(JSON j)
{
	sf::Vector2i pos = j.GetV2i("Position");
	chunkID = j.GetInt("ChunkID");
	position = pos + game->planets[planetID].GetChunk(chunkID)->position * CHUNK_SIZE;
	SetID(j.GetInt("ID"));
	SetPosition(position);
	health = j.GetInt("Health");
}
JSON Boulder::ToJSON()
{
	JSON j = JSON();
	j.AddAttribute("Position", position);
	j.AddAttribute("ChunkID", chunkID);
	j.AddAttribute("TypeID", typeID);
	j.AddAttribute("ID", id);
	j.AddAttribute("Health", health);
	return j;
}
void Boulder::Update(float dt)
{}
void Boulder::Render()
{
	game->planets[planetID].renderObjects.push_back(RenderObject {
		&sprite,
		17 });
}