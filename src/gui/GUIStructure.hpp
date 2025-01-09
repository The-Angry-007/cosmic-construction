#pragma once
#include "GUIImage.hpp"
#include "gui.hpp"
class GUIStructure : public GUIObject
{
public:
	sf::Vector2f actualSize;
	std::vector<GUIImage*> images;
	int typeID;
	GUIStructure(sf::Vector2f position, sf::Vector2f size, int typeID, std::vector<int> frames);
	void Update(float dt);
	void Render();
};