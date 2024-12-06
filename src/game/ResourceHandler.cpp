#include "ResourceHandler.hpp"
#include "Item.hpp"
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
	std::cout << "initing resource handler" << std::endl;
	itemTextures = {};
	outlineTextures = {};
	itemTable = new Table();
	std::string data = SaveHandler::ReadData("resources\\items\\itemTable.txt");
	itemTable->FromString(data);
	numItems = itemTable->records.size();
	std::vector<sf::Image> images = {};
	for (int i = 0; i < itemTable->records.size(); i++)
	{
		sf::Texture t;
		if (!t.loadFromFile("resources\\items\\" + itemTable->GetValue("ImagePath", i)))
		{
			std::cout << "failed to load item texture: row " << i << std::endl;
		}
		itemTextures.push_back(t);
		auto image = t.copyToImage();
		sf::Image newImage;
		images.push_back(image);
		images.push_back(newImage);
		newImage.create(ITEM_SIZE + 2, ITEM_SIZE + 2, sf::Color::Transparent);
		newImage.copy(image, 1, 1);
		sf::Image newImage2;
		newImage2.create(ITEM_SIZE + 3, ITEM_SIZE + 3, sf::Color::Transparent);
		newImage2.copy(newImage, 0, 0);

		for (uint i = 0; i < ITEM_SIZE + 2; i++)
		{
			for (uint j = 0; j < ITEM_SIZE + 2; j++)
			{
				if (newImage.getPixel(i, j).a != 0)
				{
					continue;
				}
				bool adj = false;
				for (int k = -1; k < 2; k++)
				{
					for (int l = -1; l < 2; l++)
					{
						int x = i + k;
						int y = j + l;
						if (k == 0 && l == 0)
						{
							continue;
						}
						if (x < 0 || x > ITEM_SIZE + 1 || y < 0 || y > ITEM_SIZE + 1)
						{
							continue;
						}
						if (newImage.getPixel(x, y).a != 0)
						{
							adj = true;
							break;
						}
					}
				}
				if (adj)
				{
					newImage2.setPixel(i, j, sf::Color::White);
				}
			}
		}
		sf::Texture outline;
		outline.create(ITEM_SIZE + 2, ITEM_SIZE + 2);
		if (!outline.loadFromImage(newImage2))
		{
			std::cout << "failed to create texture from image" << std::endl;
		}
		std::cout << outline.getSize().x << " " << outline.getSize().y << std::endl;
		outlineTextures.push_back(outline);
	}
}