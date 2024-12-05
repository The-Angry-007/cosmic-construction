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
	else if (other->index == 1)
	{
		sf::FloatRect rect(currentPos - currentSize, currentSize * 2.f);
		return RectIntersectsCircle(other->currentPos, other->currentSize.x, rect);
	}
	return false;
}

void HitboxRect::Display(bool colliding)
{
	sf::RectangleShape drawRect(sf::Vector2f(currentSize.x * 2, currentSize.y * 2));
	drawRect.setPosition(currentPos.x, currentPos.y);
	drawRect.setOrigin(sf::Vector2f(currentSize.x, currentSize.y));

	if (colliding)
	{
		drawRect.setFillColor(sf::Color::Green);
	}
	else
	{
		drawRect.setFillColor(sf::Color::Red);
	}
	window->draw(drawRect);
}

bool HitboxRect::intersectsPoint(sf::Vector2f point)
{
	sf::FloatRect rect(currentPos - currentSize, 2.f * currentSize);
	if (point.x < rect.left || point.y < rect.top)
	{
		return false;
	}
	if (point.x > rect.left + rect.width || point.y > rect.top + rect.height)
	{
		return false;
	}
	return true;
}
