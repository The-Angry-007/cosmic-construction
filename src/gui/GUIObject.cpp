#include "GUIObject.hpp"
#include "InputHandler.hpp"
GUIObject::GUIObject()
{}

//the mouse position is passed in instead of using the variable
//provided by inputhandler, as it needs to be between 0 and 1
bool GUIObject::isBlockingMouse()
{
	if (!blocksMouseInput)
	{
		return false;
	}
	if (hitbox == nullptr)
	{
		return false;
	}
	return hitbox->intersectsPoint(InputHandler::guiMP);
}

bool GUIObject::isClicked()
{
	if (InputHandler::mbPressed(sf::Mouse::Button::Left))
	{
		return isBlockingMouse();
	}
	return false;
}

void GUIObject::Update(float dt)
{}

void GUIObject::Render()
{}

GUIObject::~GUIObject()
{}