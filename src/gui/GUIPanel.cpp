#include "GUIPanel.hpp"
#include "Main.hpp"

GUIPanel::GUIPanel(sf::Vector2f position, sf::Vector2f size, sf::Color color)
{
	this->position = position;
	this->size = size;
	this->color = color;
	rect = sf::RectangleShape();
	rect.setFillColor(color);
	blocksMouseInput = false;
	hitbox = new Hitbox(sf::Vector2f(0.f, 0.f), sf::Vector2f(1.f, 1.f));
	hitbox->AddShape(new HitboxRect(position, size));
	keepAspectRatio = false;
	ratio = 1.f;
}

void GUIPanel::Update(float dt)
{
	hitbox->shapes[0]->currentPos = position;
	hitbox->shapes[0]->currentSize = size;
}

void GUIPanel::Render()
{
	sf::Vector2f newPos = sf::Vector2f(position.x * width, position.y * height);
	sf::Vector2f newSize = sf::Vector2f(size.x * width, size.y * height);
	if (keepAspectRatio)
	{
		float desiredHeight = newSize.x * ratio;
		if (desiredHeight > newSize.y)
		{
			float mult = desiredHeight / newSize.y;
			newSize.x /= mult;
			hitbox->shapes[0]->currentSize.x = newSize.x / width;
		}
		else
		{
			float desiredWidth = newSize.y / ratio;
			float mult = desiredWidth / newSize.x;
			newSize.y /= mult;
			hitbox->shapes[0]->currentSize.y = newSize.y / height;
		}
	}
	rect.setPosition(newPos);
	rect.setSize(newSize * 2.f);
	rect.setOrigin(newSize);
	window->draw(rect);
}
GUIPanel::~GUIPanel()
{
	if (hitbox != nullptr)
	{
		delete hitbox;
	}
}

void GUIPanel::SetColor(sf::Color color)
{
	this->color = color;
	rect.setFillColor(color);
}