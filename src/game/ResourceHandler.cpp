#include "ResourceHandler.hpp"

namespace ResourceHandler
{
std::vector<sf::Texture> itemTextures;
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
	}
}