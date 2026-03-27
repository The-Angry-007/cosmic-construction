#pragma once
#include "../PCH.hpp"
#include "Structure.hpp"
#include "Tree.hpp"
class SaplingPlanter : public Structure
{
public:
	int tree;
	float timeSinceTree;
	sf::Sprite topSprite = sf::Sprite(texture);
	SaplingPlanter(int id, int planetID, int direction = 0);
	void Update(float dt);
	void Render();
	void RenderPreview();
	void FromJSON(JSON j);
	JSON ToJSON();
	void SetPosition(sf::Vector2i pos);
};