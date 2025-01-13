#include "utils.hpp"
//used to check if hitboxrects collide with other hitboxrects
bool RectIntersectsRect(sf::FloatRect rect1, sf::FloatRect rect2)
{
	//split into multiple conditions to become more readable
	//first checks if the second rect's left side is past the first rect's right side
	bool cond1 = (rect2.left > rect1.left + rect1.width);
	//same as cond1 but opposite side of rect
	bool cond2 = (rect2.left + rect2.width < rect1.left);
	//same as cond1 but for y instead of x
	bool cond3 = (rect2.top > rect1.top + rect1.height);
	//same as cond2 but for y instead of x
	bool cond4 = (rect2.top + rect2.height < rect1.top);
	//only intersecting if none of the conditions are true
	if (!(cond1 || cond2 || cond3 || cond4))
	{
		return true;
	}
	//return false if not intersecting
	return false;
}

bool RectIntersectsRect(sf::IntRect rect1, sf::IntRect rect2)
{
	//split into multiple conditions to become more readable
	//first checks if the second rect's left side is past the first rect's right side
	bool cond1 = (rect2.left >= rect1.left + rect1.width);
	//same as cond1 but opposite side of rect
	bool cond2 = (rect2.left + rect2.width <= rect1.left);
	//same as cond1 but for y instead of x
	bool cond3 = (rect2.top >= rect1.top + rect1.height);
	//same as cond2 but for y instead of x
	bool cond4 = (rect2.top + rect2.height <= rect1.top);
	//only intersecting if none of the conditions are true
	if (!(cond1 || cond2 || cond3 || cond4))
	{
		return true;
	}
	//return false if not intersecting
	return false;
}
//used to check if hitboxrects collide with hitboxcircles
bool RectIntersectsCircle(sf::Vector2f pos, float r, sf::FloatRect rect)
{
	//get the closest point to the circle within the rect
	float closestX = clamp(pos.x, rect.left, rect.left + rect.width);
	float closestY = clamp(pos.y, rect.top, rect.top + rect.height);
	//find x offset and y offset
	float dx = pos.x - closestX;
	float dy = pos.y - closestY;
	//find the squared magnitude using pythagoras; sqrt is avoided as it is a slow operation
	float mag = dx * dx + dy * dy;
	//check if less than the radius squared, if so then intersects
	//as this means the closest point is within the circle
	if (mag < r * r)
	{
		return true;
	}
	//otherwise do not intersect
	return false;
}
//used to check if hitboxcircle collides with hitboxcircle
bool CircleIntersectsCircle(sf::Vector2f pos1, float r1, sf::Vector2f pos2, float r2)
{
	//find offset between centres
	sf::Vector2f d = pos2 - pos1;
	//find squared magnitude (pythagoras)
	float mag = d.x * d.x + d.y * d.y;
	//get maximum distance between centres for intersection
	float rmax = r1 + r2;
	//compare squared max distance to squared magnitude
	if (mag < rmax * rmax)
	{
		//if maximum distance > distance, then colliding
		return true;
	}
	//otherwise not intersecting
	return false;
}

//if a value is outside the range given,it becomes the closest value within a range
//otherwise the original value is returned
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
/*linear interpolation algorithm:
a and b are 2 numbers where b > a
t is a value between 0 and 1 that interpolates between a and b
0.5 = midpoint, 0 = a, 1 = b, etc*/
float Lerp(float a, float b, float t)
{
	return a + (b - a) * t;
}
//lerp but for vectors
sf::Vector2f Lerp(sf::Vector2f a, sf::Vector2f b, float t)
{
	return a + (b - a) * t;
}
//splits a string based on a split character
std::vector<std::string> Split(std::string string, char chr)
{
	//vector to store results
	std::vector<std::string> split = {};
	//the substring from the most recent split to the current character
	std::string current = "";
	int i = 0;
	//iterate through string
	while (i < string.length())
	{
		//if split character detected, add current substring to vector and reset
		if (string[i] == chr)
		{
			split.push_back(current);
			current = "";
		}
		//otherwise add next character of string
		else
		{
			current += string[i];
		}
		i++;
	}
	//add whatever's left over to the vector and return it
	split.push_back(current);
	return split;
}
//joins multiple lines together into one string with new line characters in between
std::string concat(std::vector<std::string> lines)
{
	std::string result = "";
	for (uint i = 0; i < lines.size(); i++)
	{
		result += lines[i];
		if (i != lines.size() - 1)
		{
			result += '\n';
		}
	}
	return result;
}