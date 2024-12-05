#include "Item.hpp"
#include "Main.hpp"
Item::Item(sf::Vector2f position)
{
	this->position = position;
	typeId = rand() % ResourceHandler::numItems;
	sf::Texture& t = ResourceHandler::itemTextures[typeId];
	sprite.setTexture(t);
	sprite.setOrigin((sf::Vector2f)t.getSize() / 2.f);
	hitbox = new Hitbox(sf::Vector2f(0.f, 0.f), sf::Vector2f(1.f, 1.f));
}

void Item::Update(float dt)
{
}

void Item::Render()
{
	sprite.setPosition(position);
	window->draw(sprite);
}