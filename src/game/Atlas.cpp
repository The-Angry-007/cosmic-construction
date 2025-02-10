#include "Atlas.hpp"
#include "ResourceHandler.hpp"
//constructor for the item atlas
Atlas::Atlas(std::vector<sf::Texture>& textures)
{
	positions = {};
	int rowHeight = 0;
	int rowWidth = 0;
	int totalWidth = 0;
	int totalHeight = 0;
	int maxSize = sf::Texture::getMaximumSize();
	//algorithm that finds the position of each texture. Added in rows with the height of the maximum height of the texture.
	for (uint i = 0; i < textures.size(); i++)
	{
		//increase width by width of texture
		int newWidth = rowWidth + textures[i].getSize().x;
		//if too big, move on to new row
		if (newWidth > maxSize)
		{
			totalHeight += rowHeight;
			rowHeight = 0;
			rowWidth = 0;
		}
		//if width of row is greater than width of texture, expand width of texture
		if (newWidth > totalWidth)
		{
			totalWidth = newWidth;
		}
		//if height greater than row height, increase row height
		if (textures[i].getSize().y > rowHeight)
		{
			rowHeight = textures[i].getSize().y;
		}
		//add position and expand size of row
		positions.push_back(sf::Vector2i(rowWidth, totalHeight));
		rowWidth += textures[i].getSize().x;
	}
	//add height of final row
	totalHeight += rowHeight;
	sf::Image im;
	//create image and add textures in positions calculated
	im.create(totalWidth, totalHeight);
	for (uint i = 0; i < textures.size(); i++)
	{
		auto i2 = textures[i].copyToImage();
		im.copy(i2, positions[i].x, positions[i].y);
	}
	//convert to texture
	texture.loadFromImage(im);
	this->textures = textures;
}
//constructor for the structure atlas
Atlas::Atlas(std::vector<sf::Texture>& textures, std::vector<int> ids)
{
	positions = {};
	idPoses = {};
	int currentID = -1;
	//finds where unique IDs start and stores their positions
	for (int i = 0; i < ids.size(); i++)
	{
		if (ids[i] != currentID)
		{
			currentID = ids[i];
			idPoses.push_back(i);
		}
	}
	//the code below is the same as the other constructor
	int rowHeight = 0;
	int rowWidth = 0;
	int totalWidth = 0;
	int totalHeight = 0;
	int maxSize = sf::Texture::getMaximumSize();
	//algorithm that finds the position of each texture. Added in rows with the height of the maximum height of the texture.
	for (uint i = 0; i < textures.size(); i++)
	{
		//increase width by width of texture
		int newWidth = rowWidth + textures[i].getSize().x;
		//if too big, move on to new row
		if (newWidth > maxSize)
		{
			totalHeight += rowHeight;
			rowHeight = 0;
			rowWidth = 0;
		}
		//if width of row is greater than width of texture, expand width of texture
		if (newWidth > totalWidth)
		{
			totalWidth = newWidth;
		}
		//if height greater than row height, increase row height
		if (textures[i].getSize().y > rowHeight)
		{
			rowHeight = textures[i].getSize().y;
		}
		//add position and expand size of row
		positions.push_back(sf::Vector2i(rowWidth, totalHeight));
		rowWidth += textures[i].getSize().x;
	}
	//add size of final row
	totalHeight += rowHeight;
	sf::Image im;
	//add all textures to image
	im.create(totalWidth, totalHeight);
	for (uint i = 0; i < textures.size(); i++)
	{
		auto i2 = textures[i].copyToImage();
		im.copy(i2, positions[i].x, positions[i].y);
	}
	//convert to texture
	texture.loadFromImage(im);
	this->textures = textures;
}

void Atlas::SetSprite(sf::Sprite& sprite, int id, int frameNum)
{
	//converts usage of the structure atlas to usage of the complete atlas to increase performance
	if (ResourceHandler::structureAtlas == this)
	{
		ResourceHandler::completeAtlas->SetSprite(sprite, id + 2 * ResourceHandler::numItems, frameNum);
		return;
	}
	//finds correct texture index and sets origin and texture rect of sprite accordingly
	int index = idPoses[id] + frameNum;
	sprite.setTexture(texture);
	sprite.setTextureRect(sf::IntRect(positions[index], (sf::Vector2i)textures[index].getSize()));
	sprite.setOrigin((sf::Vector2f)(textures[index].getSize()) / 2.f);
}

void Atlas::SetSprite(sf::Sprite& sprite, int id)
{
	//converts to usage of complete atlas to increase performance (this is only called for the item atlas)
	ResourceHandler::completeAtlas->SetSprite(sprite, id, 0);
}