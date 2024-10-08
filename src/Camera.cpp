#include "Include.hpp"
Camera::Camera(sf::Vector2f pos, float zoom)
{
	this->zoomInc = pow(2.f, 1.f / 7.f) - 1;
	this->pos = pos;
	this->zoom = zoom;
	targetZoom = zoom;
	view = sf::View(toFloatRect());
	windowSize = sf::Vector2u(0, 0);
	rotation = 0.f;
	bgShape = new sf::RectangleShape(sf::Vector2f(1, 1));
	bgShape->setFillColor(sf::Color::Blue);
	bgView = sf::View(sf::FloatRect(0.f, 0.f, 1.f, 1.f));
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
		float zoomRate = 1 + zoomInc;
		if (inp.scroll.y > 0)
		{
			zoomRate = 1 - zoomInc;
		}
		targetZoom *= (zoomRate);
		// // Adjust camera position to keep the point under the mouse stationary
		// sf::Vector2f mousePosRelativeToView = window->mapPixelToCoords(static_cast<sf::Vector2i>(inp.mousePos));
		// sf::Vector2f adjustment = (mousePosRelativeToView - pos) * (1 - (zoom / oldZoom));
		// pos += adjustment;
		if (targetZoom < 0.1f)
		{
			targetZoom /= zoomRate;
		}
		if (targetZoom > 100.f)
		{
			targetZoom *= zoomRate;
		}
		std::cout << targetZoom << std::endl;
	}
	zoom = targetZoom;

	prevMousePos = inp.mousePos;
}
void Camera::RenderBg()
{
	window->setView(bgView);
	window->draw(*bgShape);
	window->setView(view);
}
void Camera::RenderMenu(Menu* menu, double dt)
{
	sf::View menuView(sf::FloatRect(0.f, 0.f, width, height));
	window->setView(menuView);
	menu->Render(dt);
	UpdateView();
}
sf::FloatRect Camera::toFloatRect()
{
	return sf::FloatRect(pos.x - width * zoom / 2.f, pos.y - height * zoom / 2.f, width * zoom, height * zoom);
}

void Camera::SetBgCol(sf::Color col)
{
	bgShape->setFillColor(col);
}