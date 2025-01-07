#pragma once
#include "Structure.hpp"
#include "gui.hpp"
class StorageSilo : public Structure
{
public:
	std::vector<int> itemIDs;
	std::vector<int> itemQuantities;
	std::vector<int> neighbours;
	std::vector<sf::Sprite> sprites;
	StorageSilo(int id, int planetID);
	StorageSilo(int planetID);
	~StorageSilo();
	void SetPosition(sf::Vector2i pos);
	void SetVisualPosition(sf::Vector2i pos);
	void TryAddGroundItem(int index);
	void UpdateNeighbours();
	void Update(float dt);
	void Render();
	JSON ToJSON();
	void FromJSON(JSON j);
	void AddItem(int index);
	void RenderPreview();
	void Interact();
};