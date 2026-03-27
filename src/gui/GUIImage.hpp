#pragma once
#include "../PCH.hpp"
#include "GUIObject.hpp"

class GUIImage : public GUIObject
{
public:
	sf::Texture texture;
	sf::Sprite sprite = sf::Sprite(texture);
	bool keepAspectRatio;
	sf::Vector2f origin;
	GUIImage(sf::Vector2f position, sf::Vector2f size, std::string path);
	~GUIImage();
	void Render();
	void RenderToTexture(sf::RenderTexture* texture);
};