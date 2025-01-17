#pragma once
#include "Structure.hpp"
#include "gui.hpp"
class StorageSilo : public Structure
{
public:
	std::vector<int> items;
	std::vector<int> itemIDs;
	std::vector<int> itemQuantities;
	std::vector<int> inputNeighbours;
	std::vector<int> outputNeighbours;
	std::vector<int> previousOutputs;
	std::vector<sf::Sprite> sprites;
	StorageSilo(int id, int planetID, int direction = 0);
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
	void Destroy();
};