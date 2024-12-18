#pragma once
#include "GUIObject.hpp"
class GUIPanel : public GUIObject
{
public:
	sf::Color color;
	sf::RectangleShape rect;
	bool keepAspectRatio;
	float ratio;

	void SetColor(sf::Color color);
	void Render();
	void RenderToTexture(sf::RenderTexture* texture);
	void Update(float dt);
	GUIPanel(sf::Vector2f position, sf::Vector2f size, sf::Color color);
	~GUIPanel();
};