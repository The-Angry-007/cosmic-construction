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
		positions.push_back(sf::Vector2i(rowWidth, totalHeight));
	}
	sf::Image im;
	im.create(totalWidth, totalHeight);
	for (uint i = 0; i < textures.size(); i++)
	{
		auto i2 = textures[i].copyToImage();
		im.copy(i2, positions[i].x, positions[i].y);
	}
	im.create(100, 100);
	im.setPixel(50, 50, sf::Color::Blue);
	im.saveToFile(SaveHandler::workingDir + "\\atlas.png");
}