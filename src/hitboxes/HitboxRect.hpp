#pragma once
#include "HitboxShape.hpp"

class HitboxRect : public HitboxShape
{
public:
	HitboxRect(sf::Vector2f position, sf::Vector2f size);
	~HitboxRect();
	bool intersects(HitboxShape* other);
	bool intersectsPoint(sf::Vector2f point);

	//temporary function to test
	void Display(bool colliding);
};