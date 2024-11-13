#pragma once
#include "GUIObject.hpp"

class GUISlider : public GUIObject
{
public:
	//the object the user will grab
	GUIObject* knob;
	//the background of the slider
	GUIObject* background;
	//will display between the start and the position of the knob
	GUIObject* completion;
	//how far over the knob is from 0 to 1
	float value;

	void Update(float dt);
	void Render();
	GUISlider(sf::Vector2f position, sf::Vector2f size, GUIObject* knob, GUIObject* background, GUIObject* completion);
	~GUISlider();
};