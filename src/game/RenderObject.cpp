#include "RenderObject.hpp"
bool operator<(const RenderObject& lhs, const RenderObject& rhs)
{
	if (lhs.zindex < rhs.zindex)
	{
		return true;
	}
	return (lhs.zindex == rhs.zindex) && (lhs.sprite->getPosition().y < rhs.sprite->getPosition().y || (lhs.sprite->getPosition().y == rhs.sprite->getPosition().y && lhs.sprite->getPosition().x < rhs.sprite->getPosition().x));
	// return lhs.zindex == rhs.zindex && lhs.sprite->getPosition().y < rhs.sprite->getPosition().y;
}