#pragma once
#include "Structure.hpp"
class StorageSilo : public Structure
{
public:
	std::vector<int> itemIDs;
	std::vector<int> itemQuantities;
	std::vector<int> neighbours;
	std::vector<sf::Sprite> sprites;
	StorageSilo(int id, int planetID);
	StorageSilo(int planetID);
	void SetPosition(sf::Vector2i pos);
	void UpdateNeighbours();
	void Update(float dt);
	void Render();
	JSON ToJSON();
	void FromJSON(JSON j);
};