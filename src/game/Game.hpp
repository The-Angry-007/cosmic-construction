#pragma once
#include "Camera.hpp"
#include "Item.hpp"
#include "Planet.hpp"
#include "ToolHandler.hpp"
class Game
{
public:
	bool paused;
	std::vector<Planet> planets;
	int activePlanet;
	int loadedTimer;
	ToolHandler* toolHandler;

	Game();
	~Game();
	Planet* ActivePlanet();
	void TogglePaused();
	void NewGame();
	void LoadGame();
	void Update(float dt);
	void WorldUpdate(float dt);
	void Render();
};