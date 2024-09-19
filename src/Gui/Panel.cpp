#include "Include.hpp"
Panel::Panel(sf::Vector2f pos, sf::Vector2f size, sf::Color col)
{
	this->col = col;
	sf::Vector2f hs = size / 2.f;
	this->bounds = sf::FloatRect(pos.x - hs.x, pos.y - hs.y, pos.x + hs.x, pos.y + hs.y);
	panel.setFillColor(col);
}
Panel::Panel(sf::FloatRect bounds, sf::Color col)
{
	this->col = col;
	this->bounds = bounds;
	panel.setFillColor(col);
}
void Panel::Render()
{
	panel.setPosition(bounds.left * width, bounds.top * height);
	panel.setSize(sf::Vector2f(bounds.width * width, bounds.height * height));
	window->draw(panel);
}
bool Panel::MouseOver()
{
	sf::Vector2f p = inp.mousePos;
	return (p.x > bounds.left && p.x < bounds.left + bounds.width && p.y > bounds.top && p.y < bounds.top + bounds.height);
}