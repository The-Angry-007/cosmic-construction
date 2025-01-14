#include "TreeChopper.hpp"
#include "Main.hpp"
#include "ResourceHandler.hpp"
TreeChopper::TreeChopper(int id, int planetID, int direction)
{
	SetID(id);
	this->planetID = planetID;
	this->direction = direction;
	typeID = 3;
	tileSize = ResourceHandler::structureSizes[typeID];
	sprite = sf::Sprite();
	ResourceHandler::structureAtlas->SetSprite(sprite, typeID, direction * 15);
	blocksItems = true;
	placedByPlayer = true;
}

void TreeChopper::Update(float dt)
{}
void TreeChopper::Render()
{
	game->planets[planetID].renderObjects.push_back(RenderObject {
		&sprite,
		16 });
}
void TreeChopper::RenderPreview()
{
}