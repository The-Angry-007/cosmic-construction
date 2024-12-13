#include "Atlas.hpp"
Atlas::Atlas(std::vector<sf::Texture>& textures)
{
	positions = {};
	int rowHeight = 0;
	int rowWidth = 0;
	int totalWidth = 0;
	int totalHeight = 0;
	int maxSize = sf::Texture::getMaximumSize();
	for (uint i = 0; i < textures.size(); i++)
	{
		int newWidth = rowWidth + textures[i].getSize().x;
		if (newWidth > maxSize)
		{
			totalHeight += rowHeight;
			rowHeight = 0;
			rowWidth = 0;
		}
		if (newWidth > totalWidth)
		{
			totalWidth = newWidth;
		}
		if (textures[i].getSize().y > rowHeight)
		{
			rowHeight = textures[i].getSize().y;
		}
		positions.push_back(sf::Vector2i(rowWidth, totalHeight));
		rowWidth += textures[i].getSize().x;
	}
	totalHeight += rowHeight;
	sf::Image im;
	std::cout << totalWidth << " " << totalHeight << std::endl;
	im.create(totalWidth, totalHeight);
	for (uint i = 0; i < textures.size(); i++)
	{
		auto i2 = textures[i].copyToImage();
		im.copy(i2, positions[i].x, positions[i].y);
	}
	im.saveToFile(SaveHandler::workingDir + "\\atlas.png");
	texture.loadFromImage(im);
	this->textures = textures;
}

Atlas::Atlas(std::vector<sf::Texture>& textures, std::vector<int> ids)
{
	positions = {};
	idPoses = {};
	int currentID = -1;
	for (int i = 0; i < ids.size(); i++)
	{
		if (ids[i] != currentID)
		{
			currentID = ids[i];
			idPoses.push_back(i);
		}
	}
	int rowHeight = 0;
	int rowWidth = 0;
	int totalWidth = 0;
	int totalHeight = 0;
	int maxSize = sf::Texture::getMaximumSize();
	for (uint i = 0; i < textures.size(); i++)
	{
		int newWidth = rowWidth + textures[i].getSize().x;
		if (newWidth > maxSize)
		{
			totalHeight += rowHeight;
			rowHeight = 0;
			rowWidth = 0;
		}
		if (newWidth > totalWidth)
		{
			totalWidth = newWidth;
		}
		if (textures[i].getSize().y > rowHeight)
		{
			rowHeight = textures[i].getSize().y;
		}
		positions.push_back(sf::Vector2i(rowWidth, totalHeight));
		rowWidth += textures[i].getSize().x;
	}
	totalHeight += rowHeight;
	sf::Image im;
	std::cout << totalWidth << " " << totalHeight << std::endl;
	im.create(totalWidth, totalHeight);
	for (uint i = 0; i < textures.size(); i++)
	{
		auto i2 = textures[i].copyToImage();
		im.copy(i2, positions[i].x, positions[i].y);
	}
	im.saveToFile(SaveHandler::workingDir + "\\atlas.png");
	texture.loadFromImage(im);
	this->textures = textures;
}

void Atlas::SetSprite(sf::Sprite& sprite, int id, int frameNum)
{
	int index = idPoses[id] + frameNum;
	sprite.setTexture(texture);
	sprite.setTextureRect(sf::IntRect(positions[index], (sf::Vector2i)textures[id].getSize()));
	sprite.setOrigin((sf::Vector2f)(textures[id].getSize()) / 2.f);
}

void Atlas::SetSprite(sf::Sprite& sprite, int id)
{
	sprite.setTexture(texture);
	sprite.setTextureRect(sf::IntRect(positions[id], (sf::Vector2i)textures[id].getSize()));
	sprite.setOrigin((sf::Vector2f)(textures[id].getSize()) / 2.f);
}