#pragma once
//very simple struct used for sorting
struct RenderObject
{
	sf::Sprite* sprite;
	int zindex;
};
bool operator<(const RenderObject& lhs, const RenderObject& rhs);