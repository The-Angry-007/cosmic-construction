#pragma once
#include "Item.hpp"
#include "saving.hpp"
namespace ResourceHandler
{
extern std::vector<sf::Texture> itemTextures;
extern std::vector<sf::Texture> outlineTextures;
extern Table* itemTable;
extern int numItems;
void Init();
};