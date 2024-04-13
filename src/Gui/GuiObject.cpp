#include "Include.hpp"

GuiObject::GuiObject()
{}
GuiObject::~GuiObject()
{}

bool GuiObject::isBlockingMouse()
{
	if (!blocksMouseInput)
	{
		return false;
	}
	if (inp.mousePos.x > bounds.left && inp.mousePos.x < bounds.left + bounds.width)
	{
		if (inp.mousePos.y > bounds.top && inp.mousePos.y < bounds.top + bounds.height)
		{
			return true;
		}
	}
	return false;
}

void GuiObject::SetBounds()
{
	bounds = sf::FloatRect(pos, size);
}