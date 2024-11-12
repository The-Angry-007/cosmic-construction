#include "GUIGalaxy.hpp"
#include "Main.hpp"
#define PI 3.14159265f;
GUIGalaxy::GUIGalaxy()
{
	float dir = (float)(rand() % 360) / 180.f * PI;
	vel = sf::Vector2f(cos(dir), sin(dir));
	if (!texture.loadFromFile("resources/images/galaxy.png"))
	{
		std::cout << "galaxy failed to load in GUI galaxy" << std::endl;
		window->close();
		exit(1);
	}
	sprite.setTexture(texture);
	position = sf::Vector2f(texture.getSize().x / 2.f, texture.getSize().y / 2.f);
	speed = 100.f;
}
void GUIGalaxy::Update(float dt)
{
	position += vel * dt * speed;
	sf::FloatRect bounds(position - (sf::Vector2f)texture.getSize() / 2.f, (sf::Vector2f)texture.getSize());
	if (bounds.top > 0)
	{
		position -= vel * dt * speed;
		vel.y *= -1;
	}
	else if (bounds.top + bounds.height < height)
	{
		position -= vel * dt * speed;
		vel.y *= -1;
	}
	if (bounds.left > 0)
	{
		position -= vel * dt * speed;
		vel.x *= -1;
	}
	else if (bounds.left + bounds.width < width)
	{
		position -= vel * dt * speed;
		vel.x *= -1;
	}
}
void GUIGalaxy::Render()
{
	sprite.setPosition(position);
	sprite.setOrigin((sf::Vector2f)texture.getSize() / 2.f);
	window->draw(sprite);
}