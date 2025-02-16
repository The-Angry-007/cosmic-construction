#pragma once
#include "Hitboxes.hpp"
#include "gui.hpp"
class Camera
{
public:
	sf::Vector2f position;
	sf::Vector2f mouseStartPos;
	sf::Vector2f cameraStartPos;
	float zoom;
	float targetZoom;
	float zoomRate;
	float zoomSpeed;
	float moveSpeed;
	sf::Vector2f prevMousePos;
	Hitbox* hitbox;
	~Camera();
	Camera();
	Camera(sf::Vector2f position, float zoom);
	void Update(float dt);
	void SetView();
	sf::Vector2f WorldMousePos();
	sf::Vector2f tileToGUIPos(sf::Vector2f tilePos);
	sf::FloatRect toFloatRect();
};