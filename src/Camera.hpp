#pragma once
class Menu;
class Camera
{
public:
	sf::View view;
	sf::View bgView;
	sf::Vector2f pos;
	float zoom;
	float rotation;
	float targetZoom;
	float zoomInc;
	sf::Vector2u windowSize;
	sf::Vector2f prevMousePos;
	float zoomRate;
	sf::FloatRect toFloatRect();
	Camera(sf::Vector2f pos, float zoom);
	void UpdateView();
	void Update();
	sf::RectangleShape* bgShape;
	void RenderBg();
	void RenderMenu(Menu* menu, double dt);
	void SetBgCol(sf::Color col);
};