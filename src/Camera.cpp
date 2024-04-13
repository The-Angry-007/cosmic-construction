#include "Camera.hpp"
#include "Main.hpp"
#include "utils.hpp"
Camera::Camera(sf::Vector2f pos, float zoom)
{
	this->pos = pos;
	this->zoom = zoom;
	targetZoom = zoom;
	view = sf::View(toFloatRect());
	windowSize = sf::Vector2u(0, 0);
	rotation = 0.f;
}
void Camera::UpdateView()
{
	view = sf::View(toFloatRect());
	view.setRotation(rotation);
	window->setView(view);
}
void Camera::Update()
{
	//fix window size
	if (window->getSize() != windowSize)
	{
		windowSize = window->getSize();
		width = windowSize.x;
		height = windowSize.y;
	}
	if (inp.mbDown(sf::Mouse::Button::Middle))
	{
		sf::Vector2f offset = (prevMousePos - inp.mousePos) * zoom;
		pos += offset;
	}
	if (inp.scroll.y != 0)
	{
		float zoomRate = 1.1f;
		if (inp.scroll.y > 0)
		{
			zoomRate = 0.9f;
		}
		targetZoom *= (zoomRate * abs(inp.scroll.y));
		// // Adjust camera position to keep the point under the mouse stationary
		// sf::Vector2f mousePosRelativeToView = window->mapPixelToCoords(static_cast<sf::Vector2i>(inp.mousePos));
		// sf::Vector2f adjustment = (mousePosRelativeToView - pos) * (1 - (zoom / oldZoom));
		// pos += adjustment;
		if (targetZoom < 0.1f)
		{
			targetZoom = 0.1f;
		}
		if (targetZoom > 100.f)
		{
			targetZoom = 100.f;
		}
	}
	zoom = Lerp(zoom, targetZoom, 0.05f);

	prevMousePos = inp.mousePos;
}
void Camera::RenderMenu(Menu menu, double dt)
{
	sf::View menuView(sf::FloatRect(0.f, 0.f, width, height));
	window->setView(menuView);
	menu.Render(dt);
	UpdateView();
}
sf::FloatRect Camera::toFloatRect()
{
	return sf::FloatRect(pos.x - width * zoom / 2.f, pos.y - height * zoom / 2.f, width * zoom, height * zoom);
}