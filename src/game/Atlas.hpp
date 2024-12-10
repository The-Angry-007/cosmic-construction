#pragma once
//refer to code in old version of project to help with this
class Atlas
{
public:
	sf::Texture texture;
	std::vector<sf::Vector2i> positions;
	Atlas(std::vector<sf::Texture>& textures);
};