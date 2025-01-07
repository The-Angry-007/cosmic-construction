#pragma once
#include "GUIImage.hpp"
#include "GUILabel.hpp"
#include "GUIObject.hpp"
class GUIItem : public GUIObject
{
public:
	int typeID;
	sf::Vector2f actualSize;
	int amount;
	GUIImage* image;
	GUILabel* label;
	GUIItem(sf::Vector2f position, sf::Vector2f size, int typeID, int amount);
	void Update(float dt);
	void RenderToTexture(sf::RenderTexture* texture);
};