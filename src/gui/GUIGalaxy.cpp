#include "GUIGalaxy.hpp"
#include "Main.hpp"
#define PI 3.14159265f;
GUIGalaxy::GUIGalaxy()
{
	float mag = sqrt(0.5);
	vel = sf::Vector2f(mag, mag);
	if (!texture.loadFromFile("resources/images/galaxy.png"))
	{
		std::cout << "galaxy failed to load in GUI galaxy" << std::endl;
		window->close();
		exit(1);
	}
	sprite.setTexture(texture);
	speed = 12.f;
	size = sf::Vector2f(1.f, 1.f);
	sprite.setScale(size.x, size.y);
	sf::FloatRect bounds = sprite.getLocalBounds();
	position = sf::Vector2f(-bounds.width / 2.f, -bounds.height / 2.f);
	sprite.setPosition(position);
	sprite.setOrigin(sf::Vector2f(0.f, 0.f));
}
void GUIGalaxy::Update(float dt)
{
	position += vel * dt * speed;
	sprite.setPosition(position);
	//half the size of the texture
	sf::FloatRect bounds = sprite.getGlobalBounds();
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

	window->draw(sprite);
}