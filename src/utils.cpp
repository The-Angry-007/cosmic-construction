#include "utils.hpp"
extern bool RectIntersectsRect(sf::FloatRect rect1, sf::FloatRect rect2)
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