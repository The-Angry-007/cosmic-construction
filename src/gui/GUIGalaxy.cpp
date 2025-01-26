#include "GUIGalaxy.hpp"
#include "Main.hpp"
//constructor
GUIGalaxy::GUIGalaxy()
{
	//for the velocity to have a magnitude of 1, the x and y component must be the sqrt of 1/2
	//(sqrt(1/2)^2 + sqrt(1/2)^2 = 2 * 1/2 = 1)
	float mag = sqrt(0.5);
	vel = sf::Vector2f(mag, mag);
	//load galaxy image
	if (!texture.loadFromFile("content/resources/images/galaxy.png"))
	{
		std::cout << "galaxy failed to load in GUI galaxy" << std::endl;
		window->close();
		exit(1);
	}
	//set the texture of the sprite to the galaxy
	sprite.setTexture(texture);
	//how many pixels to move each second
	speed = 12.f;
	//the scale of the image
	size = sf::Vector2f(.8f, .8f);
	sprite.setScale(size.x, size.y);
	//set the origin to be the top left corner and set the position to be (0,0)
	sprite.setOrigin(sf::Vector2f(0.f, 0.f));
	position = sf::Vector2f(0.f, 0.f);
	sprite.setPosition(position);
}
void GUIGalaxy::Update(float dt)
{
	//using delta s = v delta t, the adjustment in position is the velocity * dt
	//the velocity will be vel * speed
	position += vel * dt * speed;
	sprite.setPosition(position);
	//get the bounds of the sprite
	sf::FloatRect bounds = sprite.getGlobalBounds();
	//if the top is below the top of the screen, reverse the y velocity
	if (bounds.top > 0)
	{
		position -= vel * dt * speed;
		vel.y *= -1;
	}
	//same with if the bottom is above the bottom of the screen
	else if (bounds.top + bounds.height < height)
	{
		position -= vel * dt * speed;
		vel.y *= -1;
	}
	//same with left side beyond the left side of the screen
	if (bounds.left > 0)
	{
		position -= vel * dt * speed;
		vel.x *= -1;
	}
	//same with right side before right side of the screen
	else if (bounds.left + bounds.width < width)
	{
		position -= vel * dt * speed;
		vel.x *= -1;
	}
}
//render just simply draws the sprite
void GUIGalaxy::Render()
{
	sprite.setPosition(position);

	window->draw(sprite);
}
