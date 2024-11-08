#include "HitboxShape.hpp"

//blank constructor as it will be overridden
HitboxShape::HitboxShape()
{}

//same with destructor
HitboxShape::~HitboxShape()
{}

void HitboxShape::SetTransform(sf::Vector2f position, sf::Vector2f size)
{
	currentPos = this->position + position;
	currentSize = sf::Vector2f(this->size.x * size.x, this->size.y * size.y);
}

void HitboxShape::ResetTransform()
{
	currentPos = position;
	currentSize = size;
}

//once again this is blank as it will be overridden
bool HitboxShape::intersects(HitboxShape* other)
{
	return false;
}

void HitboxShape::Display(bool colliding)
{
	return;
}