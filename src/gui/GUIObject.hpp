#pragma once
#include "hitboxes.hpp"
class GUIObject
{
public:
	sf::Vector2f position;
	sf::Vector2f size;
	Hitbox* hitbox;
	bool blocksMouseInput;

	virtual bool isBlockingMouse();
	virtual bool isClicked();
	//dt is an abbreviation for delta time, which is the time passed (in seconds) since the last frame.
	virtual void Update(float dt);
	virtual void Render();
	virtual void RenderToTexture(sf::RenderTexture* texture);
	GUIObject();
	virtual ~GUIObject();
};