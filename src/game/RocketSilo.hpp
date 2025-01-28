#pragma once
#include "Structure.hpp"
class RocketSilo : public Structure
{
public:
	int launchType;
	float launchTimer;
	int targetPlanetID;
	sf::Sprite rocketSprite;
	RocketSilo(int id, int planetID, int direction, int typeID);
	~RocketSilo();
	void FromJSON(JSON j);
	JSON ToJSON();
	void Update(float dt);
	void LaunchRocket();
	void Render();
	void RenderPreview();
	void UpdateNeighbours();
	void SetPosition(sf::Vector2i position);
	void SetVisualPosition(sf::Vector2i position);
	void Interact();
	bool TryAddItem(int index);
	void Destroy();
};