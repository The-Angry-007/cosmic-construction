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
}

void StorageSilo::UpdateNeighbours()
{
}
void StorageSilo::Update(float dt)
{
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
}