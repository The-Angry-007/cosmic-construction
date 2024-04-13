#include "Include.hpp"
int NumItems;
// std::string itemNames[3] = { "placeholder 1", "placeholder 2", "placeholder 3" };
std::vector<std::string> itemNames;
std::vector<sf::Texture> itemTextures;
std::vector<sf::Vector2u> texturePoses;
sf::Texture itemTextureAtlas;
void InitItems()
{
	//get all file names
	std::string dir = "resources\\textures\\items";
	std::vector<std::string> files = SaveHandler::listFiles(dir);
	NumItems = files.size();
	for (uint i = 0; i < NumItems; i++)
	{
		//remove .png from end
		itemNames.push_back(files[i].substr(dir.size() + 1, files[i].size() - 5 - dir.size()));
	}
	sf::Vector2u currentPos;
	uint textWidth = 0, textHeight = 0;
	uint rowHeight = 0;
	uint maxSize = sf::Texture::getMaximumSize();
	for (uint i = 0; i < NumItems; i++)
	{

		sf::Texture t;
		if (!t.loadFromFile("resources\\textures\\items\\" + itemNames[i] + ".png"))
		{
			window->close();
		}
		if (i == 0)
		{
			currentPos = sf::Vector2u(0, 0);
			texturePoses.push_back(currentPos);
			currentPos += sf::Vector2u(t.getSize().x, 0);
			textWidth = t.getSize().x;
			textHeight = t.getSize().y;
			rowHeight = textHeight;
		}
		else
		{
			if (currentPos.x + t.getSize().x > maxSize)
			{
				currentPos = sf::Vector2u(0, textHeight + rowHeight);
				textHeight += rowHeight;
				rowHeight = 0;
			}
			texturePoses.push_back(currentPos);
			currentPos += sf::Vector2u(t.getSize().x, 0);
			textWidth += t.getSize().x;
			if (rowHeight < t.getSize().y)
			{
				rowHeight = t.getSize().y;
			}
		}
		itemTextures.push_back(t);
	}
	sf::RenderTexture rtex;
	rtex.create(textWidth, textHeight);
	for (uint i = 0; i < NumItems; i++)
	{
		sf::Sprite temp(itemTextures[i]);
		temp.setOrigin(itemTextures[i].getSize().x / 2.f, itemTextures[i].getSize().y / 2.f);
		temp.setRotation(-90);
		temp.setPosition(texturePoses[i].x + itemTextures[i].getSize().x / 2.f, texturePoses[i].y + itemTextures[i].getSize().y / 2.f);
		rtex.draw(temp);
	}
	rtex.display();
	itemTextureAtlas = rtex.getTexture();
}

Item::Item(sf::Vector2f pos, int id)
{
	this->pos = pos;
	this->id = id;
	size = 16.f;
	vel = sf::Vector2f(0.f, 0.f);
}
void Item::Update(double dt)
{
	pos += vel * (float)dt;
	//friction
	vel *= 0.98f;
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
	size = 16.f;

	this->id = std::stoi(splitted[0]);
}