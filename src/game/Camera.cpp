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
	//the zoom rate is the (numscrollstodouble)th root of 2, so that it takes that many scrolls to double the zoom
	int numScrollsToDouble = 3;
	zoomRate = pow(2.f, 1.f / numScrollsToDouble);
	hitbox = new Hitbox(sf::Vector2f(0.f, 0.f), sf::Vector2f(1.f, 1.f));
	hitbox->AddShape(new HitboxRect(position, sf::Vector2f(zoom * width, zoom * height)));
	zoomSpeed = 25.f;
}

void Camera::Update(float dt)
{
	if (InputHandler::pressed(binds::Pan))
	{
		mouseStartPos = InputHandler::mousePos;
		cameraStartPos = position;
	}
	if (InputHandler::down(binds::Pan))
	{
		sf::Vector2f offset = InputHandler::mousePos - mouseStartPos;
		offset *= zoom;
		position = cameraStartPos - offset;
	}
	if (InputHandler::scroll.y != 0)
	{
		if (InputHandler::scroll.y > 0)
		{
			targetZoom /= zoomRate;
		}
		else
		{
			targetZoom *= zoomRate;
		}
		//minimum and maximum zoom
		if (targetZoom < 0.01f)
		{
			targetZoom *= zoomRate;
		}
		if (targetZoom > 8.f)
		{
			targetZoom /= zoomRate;
		}
	}
	//exponential decay algorithm from "Lerp smoothing is broken" https://www.youtube.com/watch?v=LSNQuFEDOyQ&t=3050s&ab_channel=FreyaHolm%C3%A9r
	zoom = targetZoom + (zoom - targetZoom) * exp(-zoomSpeed * dt);
	prevMousePos = (sf::Vector2f)sf::Mouse::getPosition(*window);
	SetView();
}
sf::FloatRect Camera::toFloatRect()
{
	//get float rect representing camera
	return sf::FloatRect(position.x - width * zoom / 2.f, position.y - height * zoom / 2.f, width * zoom, height * zoom);
}

void Camera::SetView()
{
	sf::FloatRect rect = toFloatRect();
	hitbox->shapes[0]->position = sf::Vector2f(rect.left, rect.top) + 0.5f * sf::Vector2f(rect.width, rect.height);

	auto view = sf::View(rect);
	window->setView(view);
}

sf::Vector2f Camera::WorldMousePos()
{
	return window->mapPixelToCoords((sf::Vector2i)InputHandler::mousePos);
}