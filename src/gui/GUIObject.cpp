#include "GUIObject.hpp"

GUIObject::GUIObject()
{}

//the mouse position is passed in instead of using the variable
//provided by inputhandler, as it needs to be between 0 and 1
bool GUIObject::isBlockingMouse(sf::Vector2f pos)
{
	if (!blocksMouseInput)
	{
		return false;
	}
	if (hitbox == nullptr)
	{
		return false;
	}
	return hitbox->intersectsPoint(pos);
}

void GUIObject::Update(float dt)
{}

void GUIObject::Render()
{}

GUIObject::~GUIObject()
{}