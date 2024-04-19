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

Item::Item(sf::Vector2f pos, int id, int stackSize)
{
	this->pos = pos;
	this->id = id;
	size = 16.f;
	this->stackSize = stackSize;
	sprite = new sf::Sprite(itemTextures[id]);
	sprite->setOrigin(itemTextures[id].getSize().x / 2.f, itemTextures[id].getSize().y / 2.f);
	float scale = size / itemTextures[id].getSize().x;
	sprite->setScale(scale, scale);
	vel = sf::Vector2f(0.f, 0.f);
	stackLabel.setFont(*defaultFont);
	float textScale = size / 64.f / 1.f;
	stackLabel.setCharacterSize(64);
	stackLabel.setScale(textScale, textScale);
	stackLabel.setString(std::to_string(stackSize));
	sf::FloatRect b = stackLabel.getLocalBounds();
	std::cout << b.left << " " << b.top << " " << b.width << " " << b.height;
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
	sf::FloatRect labelBounds = stackLabel.getLocalBounds();
	//need to make camera unzoom to draw text then rezoom to prevent blurry
	labelBounds.left *= stackLabel.getScale().x;
	labelBounds.width *= stackLabel.getScale().x;
	labelBounds.height *= stackLabel.getScale().y;
	labelBounds.height *= stackLabel.getScale().y;
	stackLabel.setPosition(sf::Vector2f((int)(pos.x + size / 2.f - labelBounds.width - labelBounds.left), (int)(pos.y + size / 2.f - labelBounds.height - labelBounds.top)));
	window->draw(stackLabel);
}
std::string Item::toString()
{
	std::string str = "";
	str += std::to_string(id) + " ";
	str += std::to_string(pos.x) + " " + std::to_string(pos.y) + " ";
	str += std::to_string(vel.x) + " " + std::to_string(vel.y) + " ";
	str += std::to_string(stackSize);
	return str;
}

Item::Item(std::string str)
{
	std::vector<std::string> splitted = split(str, ' ');
	this->pos = sf::Vector2f(std::stof(splitted[1]), std::stof(splitted[2]));
	this->vel = sf::Vector2f(std::stof(splitted[3]), std::stof(splitted[4]));

	this->id = std::stoi(splitted[0]);
	this->stackSize = std::stoi(splitted[5]);
	sprite = new sf::Sprite(itemTextures[id]);
	sprite->setOrigin(itemTextures[id].getSize().x / 2.f, itemTextures[id].getSize().y / 2.f);
}