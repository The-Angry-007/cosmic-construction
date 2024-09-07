#include "Item.hpp"
#include "Main.hpp"
#include "utils.hpp"
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

Item::Item(sf::Vector2f pos, int id)
{
	this->pos = pos;
	this->id = id;
	size = 16.f;
	sprite = new sf::Sprite(itemTextures[id]);
	sprite->setOrigin(itemTextures[id].getSize().x / 2.f, itemTextures[id].getSize().y / 2.f);
	float scale = size / itemTextures[id].getSize().x;
	sprite->setScale(scale, scale);
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
std::string Item::toString()
{
	std::string str = "";
	str += std::to_string(id) + " ";
	str += std::to_string(pos.x) + " " + std::to_string(pos.y) + " ";
	str += std::to_string(vel.x) + " " + std::to_string(vel.y) + " ";
	return str;
}

Item::Item(std::string str)
{
	std::vector<std::string> splitted = split(str, ' ');
	this->pos = sf::Vector2f(std::stof(splitted[1]), std::stof(splitted[2]));
	this->vel = sf::Vector2f(std::stof(splitted[3]), std::stof(splitted[4]));

	this->id = std::stoi(splitted[0]);
	sprite = new sf::Sprite(itemTextures[id]);
	sprite->setOrigin(itemTextures[id].getSize().x / 2.f, itemTextures[id].getSize().y / 2.f);
}