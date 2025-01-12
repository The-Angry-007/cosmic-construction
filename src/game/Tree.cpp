#include "Tree.hpp"
#include "Main.hpp"
#include "ResourceHandler.hpp"
Tree::Tree(int id, int planetID)
{
	SetID(id);
	this->planetID = planetID;
	typeID = 2;
	health = 3;
	tileSize = ResourceHandler::structureSizes[typeID];
	sprite = sf::Sprite();
	ResourceHandler::structureAtlas->SetSprite(sprite, 2, 0);
}

Tree::Tree(int planetID)
{
	this->planetID = planetID;
	this->planetID = planetID;
	typeID = 2;
	health = 3;
	tileSize = ResourceHandler::structureSizes[typeID];
	sprite = sf::Sprite();
	ResourceHandler::structureAtlas->SetSprite(sprite, 2, 0);
}

Tree ::~Tree()
{}

void Tree::FromJSON(JSON j)
{
	sf::Vector2i pos = j.GetV2i("Position");
	chunkID = j.GetInt("ChunkID");
	position = pos + game->planets[planetID].GetChunk(chunkID)->position * CHUNK_SIZE;
	id = j.GetInt("ID");
	SetPosition(position);
	health = j.GetInt("Health");
}
JSON Tree::ToJSON()
{
	JSON j = JSON();
	j.AddAttribute("Position", position);
	j.AddAttribute("ChunkID", chunkID);
	j.AddAttribute("TypeID", typeID);
	j.AddAttribute("ID", id);
	j.AddAttribute("Health", health);
	return j;
}
void Tree::Update(float dt)
{}
void Tree::Render()
{
	game->planets[planetID].renderObjects.push_back(RenderObject {
		&sprite,
		50 });
}