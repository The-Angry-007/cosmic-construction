#pragma once
#include "saving.hpp"
//refer to code in old version of project to help with this
class Atlas
{
public:
	sf::Texture texture;
	std::vector<sf::Texture> textures;
	std::vector<sf::Vector2i> positions;
	std::vector<int> idPoses;
	Atlas(std::vector<sf::Texture>& textures);
	Atlas(std::vector<sf::Texture>& textures, std::vector<int> ids);
	void SetSprite(sf::Sprite& sprite, int id);
	void SetSprite(sf::Sprite& sprite, int id, int frameNum);
};