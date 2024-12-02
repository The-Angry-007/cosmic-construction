#include "Item.hpp"
#include "Main.hpp"

Item::Item(sf::Vector2f position)
{
	this->position = position;
}

void Item::Update(float dt)
{
}

void Item::Render()
{
	sf::RectangleShape rect(sf::Vector2f(ITEM_SIZE, ITEM_SIZE));
	rect.setOrigin(ITEM_SIZE / 2.f, ITEM_SIZE / 2.f);
	rect.setPosition(position);
	rect.setFillColor(sf::Color::Blue);
	window->draw(rect);
}