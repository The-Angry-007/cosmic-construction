#include "HitboxRect.hpp"
#include "Main.hpp"
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
		//float rect requires top left corner and total width and height,
		//pos and size are centre position and half of total width and height
		sf::FloatRect rect1(currentPos - currentSize, currentSize * 2.f);
		sf::FloatRect rect2(other->currentPos - other->currentSize, other->currentSize * 2.f);
		return RectIntersectsRect(rect1, rect2);
	}
	return false;
}

void HitboxRect::Display()
{
	sf::RectangleShape drawRect(currentSize * 2.f);
	drawRect.setPosition(currentPos);
	drawRect.setOrigin(currentSize);
	window->draw(drawRect);
}