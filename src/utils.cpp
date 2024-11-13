#include "utils.hpp"
bool RectIntersectsRect(sf::FloatRect rect1, sf::FloatRect rect2)
{
	//split into multiple conditions to become more readable
	bool cond1 = (rect2.left > rect1.left + rect1.width);
	bool cond2 = (rect2.left + rect2.width < rect1.left);
	bool cond3 = (rect2.top > rect1.top + rect1.height);
	bool cond4 = (rect2.top + rect2.height < rect1.top);
	if (!(cond1 || cond2 || cond3 || cond4))
	{
		return true;
	}
	return false;
}

bool RectIntersectsCircle(sf::Vector2f pos, float r, sf::FloatRect rect)
{
	//get the closest point to the circle within the rect
	float closestX = clamp(pos.x, rect.left, rect.left + rect.width);
	float closestY = clamp(pos.y, rect.top, rect.top + rect.height);
	//find offset
	float dx = pos.x - closestX;
	float dy = pos.y - closestY;
	//find the squared magnitude
	float mag = dx * dx + dy * dy;
	//check if less than the radius squared, if so then intersects
	if (mag < r * r)
	{
		return true;
	}
	//otherwise do not intersect
	return false;
}

bool CircleIntersectsCircle(sf::Vector2f pos1, float r1, sf::Vector2f pos2, float r2)
{
	//find offset between centres
	sf::Vector2f d = pos2 - pos1;
	//find squared magnitude
	float mag = d.x * d.x + d.y * d.y;
	//get maximum distance between centres for intersection
	float r = r1 + r2;
	//compare squared distance to squared magnitude
	if (mag < r * r)
	{
		return true;
	}
	//otherwise not intersecting
	return false;
}

float clamp(float val, float min, float max)
{
	if (val < min)
	{
		return min;
	}
	if (val > max)
	{
		return max;
	}
	return val;
}

float Lerp(float a, float b, float t)
{
	return a + (b - a) * t;
}

sf::Vector2f Lerp(sf::Vector2f a, sf::Vector2f b, float t)
{
	return a + (b - a) * t;
}