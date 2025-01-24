#pragma once
#include "Structure.hpp"
class RecipeStructure : public Structure
{
public:
	//number of stone outputted in a row
	std::vector<int> neighbours;
	int numStone;
	int outputItem;
	int lastOutputDir;
	RecipeStructure(int id, int planetID, int direction, int typeID);
	~RecipeStructure();
	void FromJSON(JSON j);
	JSON ToJSON();
	void Update(float dt);
	void Render();
	void RenderPreview();
	void UpdateNeighbours();
	void SetPosition(sf::Vector2i position);
	void SetVisualPosition(sf::Vector2i position);
	void Interact();
	bool TryAddItem(int index);
	void Destroy();
};