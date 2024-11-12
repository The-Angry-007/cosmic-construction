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
	bgObj->Render();
	labelObj->Render();
}
void GUIButton::Update(float dt)
{
	if (bgObj->isClicked() && clickFunc != nullptr)
	{
		clickFunc(this);
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