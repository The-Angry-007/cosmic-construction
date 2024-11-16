#pragma once
#include "GUIImage.hpp"
#include "GUIObject.hpp"
#include "GUIPanel.hpp"

class GUICheckbox : public GUIObject
{
public:
	bool checked;
	GUIImage* checkImage;
	GUIPanel* bgObj;
	std::vector<GUICheckbox*> exclusives;

	GUICheckbox(sf::Vector2f position, sf::Vector2f size, sf::Color col);
	void Update(float dt);
	void Render();
};