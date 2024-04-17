#include "Item.hpp"
#include "Main.hpp"
int NumItems = 3;
std::string itemNames[3] = { "placeholder 1", "placeholder 2", "placeholder 3" };
std::vector<sf::Texture> itemTextures;
void InitItems()
{
	for (uint i = 0; i < NumItems; i++)
	{
		sf::Texture t;
		if (!t.loadFromFile("resources\\textures\\items\\" + itemNames[i] + ".png"))
		{
			window->close();
		}
		itemTextures.push_back(t);
	}
}

Item::Item(sf::Vector2f pos, int id, int stackSize)
{
	this->pos = pos;
	this->id = id;
	this->stackSize = stackSize;
	sprite = new sf::Sprite(itemTextures[id]);
	sprite->setOrigin(itemTextures[id].getSize().x / 2.f, itemTextures[id].getSize().y / 2.f);
	vel = sf::Vector2f(0.f, 0.f);
}
void Item::Update(double dt)
{
	pos += vel * (float)dt;
	//friction
	vel *= 0.98f;
}
void Item::Render()
{
	sprite->setPosition(pos.x, pos.y);
	window->draw(*sprite);
}