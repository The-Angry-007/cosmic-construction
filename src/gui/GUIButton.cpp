#include "GUIButton.hpp"
#include "ClickFuncs.hpp"

GUIButton::GUIButton(sf::Vector2f position, sf::Vector2f size, GUIObject* bgObj, GUIObject* labelObj)
{
	this->position = position;
	this->size = size;
	this->bgObj = bgObj;
	this->labelObj = labelObj;
	bgObj->blocksMouseInput = true;
	clickFunc = ClickFuncs::blankFunc;
}
void GUIButton::Render()
{
	if (bgObj != nullptr)
	{
		bgObj->Render();
	}
	if (labelObj != nullptr)
	{
		labelObj->Render();
	}
}
void GUIButton::Update(float dt)
{

	if (bgObj->isClicked())
	{
		clickFunc();
	}
}
GUIButton::~GUIButton()
{
	if (bgObj != nullptr)
	{
		delete bgObj;
	}
	if (labelObj != nullptr)
	{
		delete labelObj;
	}
}

bool GUIButton::isBlockingMouse()
{
	return bgObj->isBlockingMouse();
}
bool GUIButton::isClicked()
{
	return bgObj->isClicked();
}