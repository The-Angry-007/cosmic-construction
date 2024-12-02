#include "Camera.hpp"
#include "InputHandler.hpp"
#include "Main.hpp"
#include "binds.hpp"
Camera::Camera(sf::Vector2f position, float zoom)
{
	this->position = position;
	this->zoom = zoom;
	targetZoom = zoom;
	prevMousePos = InputHandler::mousePos;
	//what the zoom is multiplied by; 2^1/7 so that 7 scrolls exactly doubles the zoom
	zoomRate = pow(2.f, 1.f / 1.7f) - 1.f;
	hitbox = new Hitbox(sf::Vector2f(0.f, 0.f), sf::Vector2f(1.f, 1.f));
	hitbox->AddShape(new HitboxRect(position, sf::Vector2f(zoom * width, zoom * height)));
}

void Camera::Update(float dt)
{

	if (InputHandler::down(binds::Pan))
	{
		sf::Vector2f offset = (prevMousePos - InputHandler::mousePos) * zoom;
		position += offset;
	}
	if (InputHandler::scroll.y != 0)
	{
		float zoomInc = 1 + zoomRate;
		if (InputHandler::scroll.y < 0)
		{
			zoomInc = 1 - zoomRate;
		}
		targetZoom *= zoomInc;
		//minimum and maximum zoom
		if (targetZoom < 0.1f)
		{
			targetZoom /= zoomInc;
		}
		if (targetZoom > 100.f)
		{
			targetZoom *= zoomInc;
		}
	}
	zoom = targetZoom;
	prevMousePos = InputHandler::mousePos;
	sf::FloatRect rect = toFloatRect();
	hitbox->shapes[0]->position = sf::Vector2f(rect.left, rect.top) + 0.5f * sf::Vector2f(rect.width, rect.height);

	auto view = sf::View(rect);
	window->setView(view);
}
sf::FloatRect Camera::toFloatRect()
{
	//get float rect representing camera
	return sf::FloatRect(position.x - width * zoom / 2.f, position.y - height * zoom / 2.f, width * zoom, height * zoom);
}