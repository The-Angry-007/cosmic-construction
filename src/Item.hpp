#pragma once
class Item
{
public:
	int id;
	sf::Vector2f pos;
	sf::Vector2f vel;
	float size;
	// sf::Sprite* sprite;
	Item(sf::Vector2f pos, int id);
	void Update(double dt);
	std::string toString();
	Item(std::string str);
};

extern std::vector<std::string> itemNames;
extern int NumItems;
extern std::vector<sf::Texture> itemTextures;
extern sf::Texture itemTextureAtlas;
extern std::vector<sf::Vector2u> texturePoses;
extern void InitItems();