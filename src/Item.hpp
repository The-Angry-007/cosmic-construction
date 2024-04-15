#pragma once
class Item
{
public:
	int id;
	sf::Vector2f pos;
	sf::Vector2f vel;
	float vertVel;
	float height;
	int stackSize;
	sf::Sprite* sprite;
	Item(sf::Vector2f pos, float height, int id, int stackSize);
	void Update(double dt);
	void Render();
};

extern std::string itemNames[3];
extern int NumItems;
extern std::vector<sf::Texture> itemTextures;
extern void InitItems();