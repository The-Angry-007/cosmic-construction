#include "HitboxCircle.hpp"
#include "Main.hpp"
#include "utils.hpp"

HitboxCircle::HitboxCircle(sf::Vector2f position, float radius)
{
	this->position = position;
	this->size = sf::Vector2f(radius, radius);
	this->currentPos = position;
	this->currentSize = this->size;
	index = 1;
}

HitboxCircle::~HitboxCircle()
{}

bool HitboxCircle::intersects(HitboxShape* other)
{
	if (other->index == 0)
	{
		sf::FloatRect rect(other->currentPos - other->currentSize, 2.f * other->currentSize);
		return RectIntersectsCircle(currentPos, currentSize.x, rect);
	}
	else if (other->index == 1)
	{
		return CircleIntersectsCircle(currentPos, currentSize.x, other->currentPos, other->currentSize.x);
	}
	return false;
}

void HitboxCircle::Display(bool colliding)
{
	sf::CircleShape circle;
	circle.setPosition(currentPos);
	circle.setRadius(currentSize.x);
	circle.setOrigin(currentSize);

	if (colliding)
	{
		circle.setFillColor(sf::Color::Green);
	}
	else
	{
		circle.setFillColor(sf::Color::Red);
	}
	window->draw(circle);
}