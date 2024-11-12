#pragma once
#include "GUIObject.hpp"

class GUIImage : public GUIObject
{
public:
	sf::Texture texture;
	sf::Sprite sprite;
	bool keepAspectRatio;
	GUIImage(sf::Vector2f position, sf::Vector2f size, std::string path);
	~GUIImage();
	void Render();
};