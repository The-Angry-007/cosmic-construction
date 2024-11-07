#include "HitboxRect.hpp"
#include "utils.hpp"
HitboxRect::HitboxRect(sf::Vector2f position, sf::Vector2f size)
{
	this->position = position;
	this->size = size;
	currentPos = position;
	currentSize = size;
	index = 0;
}

HitboxRect::~HitboxRect()
{}

bool HitboxRect::intersects(HitboxShape* other)
{
	if (other->index == 0)
	{
		sf::FloatRect rect1(currentPos, currentSize);
		sf::FloatRect rect2(other->currentPos, other->currentSize);
		return RectIntersectsRect(rect1, rect2);
	}
	return false;
}