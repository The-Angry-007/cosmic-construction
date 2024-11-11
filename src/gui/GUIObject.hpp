#pragma once
#include "hitboxes/Hitboxes.hpp"
class GUIObject
{
public:
	sf::Vector2f position;
	sf::Vector2f size;
	sf::FloatRect* container;
	Hitbox* hitbox;
	bool blocksMouseInput;

	bool isBlockingMouse(sf::Vector2f pos);
	//dt is an abbreviation for delta time, which is the time passed (in seconds) since the last frame.
	virtual void Update(float dt);
	virtual void Render();
	GUIObject();
	virtual ~GUIObject();
};