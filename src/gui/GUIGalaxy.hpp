#pragma once
#include "GUIObject.hpp"

//the galaxy that scrolls in the background of the main menu
class GUIGalaxy : public GUIObject
{
public:
	sf::Texture texture;
	sf::Sprite sprite;
	float speed;
	sf::Vector2f vel;

	void Update(float dt);
	void Render();
	GUIGalaxy();
};