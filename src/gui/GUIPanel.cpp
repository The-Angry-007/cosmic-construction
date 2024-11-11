#include "GUIPanel.hpp"
#include "Main.hpp"

GUIPanel::GUIPanel(sf::Vector2f position, sf::Vector2f size, sf::Color color)
{
	this->position = position;
	this->size = size;
	this->color = color;
	rect = sf::RectangleShape();
	blocksMouseInput = false;
	hitbox = new Hitbox(sf::Vector2f(0.f, 0.f), sf::Vector2f(1.f, 1.f));
	hitbox->AddShape(new HitboxRect(position, size));
}

void GUIPanel::Render()
{
	sf::Vector2f newPos = sf::Vector2f(position.x * width, position.y * height);
	sf::Vector2f newSize = sf::Vector2f(size.x * width, size.y * height);

	rect.setPosition(newPos);
	rect.setSize(newSize * 2.f);
	rect.setOrigin(newSize);
	window->draw(rect);
}
GUIPanel::~GUIPanel()
{
	if (container != nullptr)
	{
		delete container;
	}
	if (hitbox != nullptr)
	{
		delete hitbox;
	}
}