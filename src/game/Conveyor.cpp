#include "Conveyor.hpp"
#include "Main.hpp"
#include "ResourceHandler.hpp"
Conveyor::Conveyor(int id, int planetID, int direction)
{
	SetID(id);
	this->planetID = planetID;
	typeID = 0;
	this->direction = direction;
	tileSize = ResourceHandler::structureSizes[typeID];
	ResourceHandler::structureAtlas->SetSprite(sprite, direction);
}
void Conveyor::Update(float dt)
{
}
void Conveyor::Render()
{
	window->draw(sprite);
}
