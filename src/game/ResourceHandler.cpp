#include "ResourceHandler.hpp"
#define inBounds(x, y) (x >= 0 && x < ITEM_SIZE && y >= 0 && y < ITEM_SIZE)
namespace ResourceHandler
{
std::vector<sf::Texture> itemTextures;
std::vector<sf::Texture> outlineTextures;
Table* itemTable;
int numItems = 0;
}

void ResourceHandler::Init()
{
	itemTable = new Table();
	std::string data = SaveHandler::ReadData("resources\\items\\itemTable.txt");
	itemTable->FromString(data);
	numItems = itemTable->records.size();
	for (uint i = 0; i < numItems; i++)
	{
		sf::Texture t;
		if (!t.loadFromFile("resources\\items\\" + itemTable->GetValue("ImagePath", i)))
		{
			std::cout << "failed to load item texture: row " << i << std::endl;
		}
		itemTextures.push_back(t);
		auto image = t.copyToImage();
		sf::Image newImage;
		newImage.create(ITEM_SIZE + 2, ITEM_SIZE + 2, sf::Color::Transparent);
		sf::Texture outline;
		for (int i = 0; i < ITEM_SIZE + 2; i++)
		{
			for (int j = 0; j < ITEM_SIZE + 2; j++)
			{
				int x = j - 1;
				int y = i - 1;
				if (inBounds(x, y) && image.getPixel(x, y).a != 0)
				{
					newImage.setPixel(j, i, image.getPixel(x, y));
					continue;
				}
				bool adjacent = false;
				bool doDiagonal = true;
				for (int k = -1; k < 2; k++)
				{
					for (int l = -1; l < 2; l++)
					{
						if (l == 0 && k == 0)
						{
							continue;
						}
						if (!doDiagonal && (k != 0 && l != 0))
						{
							continue;
						}
						int nx = x + k;
						int ny = y + l;
						if (inBounds(nx, ny) && image.getPixel(nx, ny).a != 0)
						{
							adjacent = true;
						}
					}
				}
				if (adjacent)
				{
					newImage.setPixel(j, i, sf::Color::White);
				}
			}
		}
		outline.loadFromImage(newImage);
		outlineTextures.push_back(outline);
	}
}