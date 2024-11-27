#include "GUIButton.hpp"
#include "ClickFuncs.hpp"
//constructor for the button. takes a position, size, background object (necessary) and label object (can be a nullptr (meaning no object provided)).
GUIButton::GUIButton(sf::Vector2f position, sf::Vector2f size, GUIObject* bgObj, GUIObject* labelObj)
{
	this->position = position;
	this->size = size;
	//buttons have a background and a label
	this->bgObj = bgObj;
	this->labelObj = labelObj;
	//by default, most gui objects do not block mouse input, however this is wanted for buttons
	bgObj->blocksMouseInput = true;
	//sets the click function to the default
	clickFunc = ClickFuncs::blankFunc;
}
void GUIButton::Render()
{
	//background object is never going to be nullptr so always render.
	bgObj->Render();
	//only render label if it isn't a nullptr
	if (labelObj != nullptr)
	{
		labelObj->Render();
	}
}
void GUIButton::Update(float dt)
{
	//same logic as in render function.
	bgObj->Update(dt);
	if (labelObj != nullptr)
	{
		labelObj->Update(dt);
	}
	//call the click function if the button is clicked.
	if (isClicked())
	{
		clickFunc();
	}
}
//destructor: delete any pointers that arent nullptrs.
GUIButton::~GUIButton()
{
	delete bgObj;
	if (labelObj != nullptr)
	{
		delete labelObj;
	}
}
//just returns whether the background object is blocking the mouse.
bool GUIButton::isBlockingMouse()
{
	return bgObj->isBlockingMouse();
}
//just returns whether the background object is clicked.
bool GUIButton::isClicked()
{
	return bgObj->isClicked();
}