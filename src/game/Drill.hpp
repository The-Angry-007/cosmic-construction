#pragma once
#include "Structure.hpp"
class Drill : public Structure
{
public:
	//number of stone outputted in a row
	std::vector<int> neighbours;
	int numStone;
	float timeSinceOutput;
	float animProgress;
	float timePerFrame;
	int currentFrame;
	int outputItem;
	int lastOutputDir;
	sf::Sprite groundSprite;
	Drill(int id, int planetID, int direction);
	~Drill();
	void FromJSON(JSON j);
	JSON ToJSON();
	void Update(float dt);
	void Render();
	void RenderPreview();
	void UpdateNeighbours();
	void SetPosition(sf::Vector2i position);
	void SetVisualPosition(sf::Vector2i position);
	void Interact();
};