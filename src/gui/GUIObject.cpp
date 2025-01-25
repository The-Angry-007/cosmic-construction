#include "GUIObject.hpp"
#include "InputHandler.hpp"
GUIObject::GUIObject()
{}

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
{
	if (hitbox != nullptr)
	{
		delete hitbox;
	}
}

void GUIObject::RenderToTexture(sf::RenderTexture* texture)
{}
