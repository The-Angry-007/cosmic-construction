#pragma once
#include "Camera.hpp"
#include "Item.hpp"
#include "Planet.hpp"
class Game
{
public:
	bool paused;
	std::vector<Planet> planets;
	int activePlanet;
	int loadedTimer;
	Game();
	~Game();
	Planet* ActivePlanet();
	void TogglePaused();
	void NewGame();
	void LoadGame();
	void Update(float dt);
	void Render();
};