#pragma once
#include "Atlas.hpp"
#include "Item.hpp"
#include "saving.hpp"
namespace ResourceHandler
{
extern std::vector<sf::Texture> itemTextures;
extern std::vector<sf::Texture> itemOutlines;
extern std::vector<sf::Texture> structureTextures;
extern sf::Texture itemAtlas;
extern sf::Texture structureAtlas;
extern std::vector<sf::Vector2i> structureSizes;
extern std::vector<sf::Texture> structureOutlines;
extern Table* itemTable;
extern Table* structureTable;
extern int numItems;
extern int numStructures;
void Init();
sf::Texture GenerateOutline(sf::Texture& texture);
};