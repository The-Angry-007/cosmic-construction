#pragma once
#include "HitboxShape.hpp"

class HitboxCircle : public HitboxShape
{
public:
	HitboxCircle(sf::Vector2f position, float radius);
	~HitboxCircle();
	bool intersects(HitboxShape* other);

	void Display(std::vector<HitboxShape*> shapes);
};