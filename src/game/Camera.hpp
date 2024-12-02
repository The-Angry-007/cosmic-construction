#pragma once
#include "Hitboxes.hpp"
#include "gui.hpp"
class Camera
{
public:
	sf::Vector2f position;
	float zoom;
	float targetZoom;
	float zoomRate;
	sf::Vector2f prevMousePos;
	Hitbox* hitbox;
	~Camera();
	Camera(sf::Vector2f position, float zoom);
	void Update(float dt);
	sf::FloatRect toFloatRect();
};