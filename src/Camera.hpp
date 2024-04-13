#pragma once
class Menu;
class Camera
{
public:
	sf::View view;
	sf::Vector2f pos;
	float zoom;
	float rotation;
	float targetZoom;
	sf::Vector2u windowSize;
	sf::Vector2f prevMousePos;
	float zoomRate;
	sf::FloatRect toFloatRect();
	Camera(sf::Vector2f pos, float zoom);
	void UpdateView();
	void Update();
	void RenderMenu(Menu menu, double dt);
};