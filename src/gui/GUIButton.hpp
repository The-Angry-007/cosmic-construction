#pragma once
#include "GUIObject.hpp"
class GUIButton : public GUIObject
{
public:
	GUIObject* bgObj;
	GUIObject* labelObj;
	GUIObject* dimObj;
	//a variable representing a function that returns void and takes in a pointer to a button object
	std::function<void()> clickFunc;

	GUIButton(sf::Vector2f position, sf::Vector2f size, GUIObject* bgObj, GUIObject* labelObj);
	~GUIButton();
	void Render();
	void Update(float dt);
	bool isClicked();
	bool isBlockingMouse();
};