#include "ResourceHandler.hpp"
#define inBounds(x, y) (x >= 0 && x < ITEM_SIZE && y >= 0 && y < ITEM_SIZE)
namespace ResourceHandler
{
std::vector<sf::Texture> itemTextures;
std::vector<sf::Texture> itemOutlines;
std::vector<sf::Texture> structureTextures;
std::vector<sf::Vector2f> structureOrigins;
std::vector<sf::Texture> structureOutlines;
std::vector<sf::Vector2i> structureSizes;
Atlas* itemAtlas;
Atlas* structureAtlas;
Table* itemTable;
Table* structureTable;
int numItems = 0;
int numStructures = 0;
}

void ResourceHandler::Init()
{
	//items
	itemTable = new Table();
	std::string data = SaveHandler::ReadData("resources\\items\\itemTable.txt");
	itemTable->FromString(data);
	numItems = itemTable->records.size();
	std::vector<sf::Texture> allItems = {};
	for (uint i = 0; i < numItems; i++)
	{
		sf::Texture t;
		if (!t.loadFromFile("resources\\items\\" + itemTable->GetValue("ImagePath", i)))
		{
			std::cout << "failed to load item texture: row " << i << std::endl;
		}
		itemTextures.push_back(t);
		sf::Texture outlineTexture = GenerateOutline(t);
		itemOutlines.push_back(outlineTexture);
		allItems.push_back(itemTextures[i]);
	}
	for (uint i = 0; i < numItems; i++)
	{
		allItems.push_back(itemOutlines[i]);
	}

	itemAtlas = new Atlas(allItems);
	//structures
	structureTable = new Table();
	data = SaveHandler::ReadData("resources\\structures\\structureTable.txt");
	structureTable->FromString(data);
	numStructures = structureTable->records.size();
	for (uint i = 0; i < numStructures; i++)
	{
		sf::Texture t;
		if (!t.loadFromFile("resources\\structures\\" + structureTable->GetValue("ImagePath", i)))
		{
			std::cout << "failed to load structure texture: row" << i << std::endl;
		}
		structureTextures.push_back(t);
		sf::Texture outlineTexture = GenerateOutline(t);
		structureOutlines.push_back(outlineTexture);
		sf::Vector2i size(0, 0);
		size.x = std::stoi(structureTable->GetValue("SizeX", i));
		size.y = std::stoi(structureTable->GetValue("SizeY", i));
		structureSizes.push_back(size);
	}
	structureAtlas = new Atlas(structureTextures);
}

sf::Texture ResourceHandler::GenerateOutline(sf::Texture& texture)
{
	auto image = texture.copyToImage();
	sf::Image newImage;
	newImage.create(texture.getSize().x + 2, texture.getSize().y + 2, sf::Color::Transparent);
	sf::Texture outline;
	for (int i = 0; i < texture.getSize().y + 2; i++)
	{
		for (int j = 0; j < texture.getSize().x + 2; j++)
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
	return outline;
}
