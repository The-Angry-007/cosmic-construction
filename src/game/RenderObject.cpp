#include "RenderObject.hpp"
bool operator<(const RenderObject& lhs, const RenderObject& rhs)
{
	float y1 = lhs.sprite->getPosition().y + lhs.zindex;
	float y2 = rhs.sprite->getPosition().y + rhs.zindex;
	if (y1 != y2)
	{
		return y1 < y2;
	}
	return lhs.sprite->getPosition().x < rhs.sprite->getPosition().x;
}