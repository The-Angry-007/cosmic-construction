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
	virtual void Update(float dt);
	virtual void Render();
	virtual void RenderToTexture(sf::RenderTexture* texture);
	GUIObject();
	virtual ~GUIObject();
};
