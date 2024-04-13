#pragma once
#include "box2d/box2d.h"
class Part
{
public:
	sf::Texture* texture;
	sf::Sprite* sprite;
	float defaultRotation;
	int index;
	b2Body* body;
	virtual void Render() = 0;
	virtual void Update(double dt) = 0;
	virtual std::string toString() = 0;
};