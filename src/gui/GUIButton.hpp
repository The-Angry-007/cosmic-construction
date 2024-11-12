#pragma once
#include "GUIObject.hpp"
class GUIButton : public GUIObject
{
public:
	GUIObject* bgObj;
	GUIObject* labelObj;
	//a variable representing a function that returns void and takes in a pointer to a button object
	std::function<void(GUIButton*)> clickFunc;

	GUIButton(sf::Vector2f position, sf::Vector2f size, GUIObject* bgObj, GUIObject* labelObj);
	~GUIButton();
	void Render();
	void Update(float dt);
};