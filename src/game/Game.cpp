#include "Game.hpp"
#include "InputHandler.hpp"
#include "Main.hpp"
#include "binds.hpp"
Game::Game()
{
	paused = false;
	planets = {};

	activePlanet = 0;
	planets.push_back(Planet(0));
	loadedTimer = 5;
	toolHandler = new ToolHandler();
}
Game::~Game()
{
}

void Game::NewGame()
{
	for (uint i = 0; i < planets.size(); i++)
	{
		planets[i].Init(false);
	}
}
void Game::TogglePaused()
{
	paused = !paused;
	if (paused)
	{
		guihandler.activeGui = 6;
		guihandler.openedGuis[guihandler.openedGuis.size() - 1] = 6;
	}
	else
	{
		guihandler.activeGui = 5;
		guihandler.openedGuis[guihandler.openedGuis.size() - 1] = 5;
	}
}
void Game::LoadGame()
{
	for (uint i = 0; i < planets.size(); i++)
	{
		planets[i].Init(true);
	}
	loadedTimer = 5;
}
void Game::Update(float dt)
{
	if (loadedTimer > 0)
	{
		loadedTimer--;
		return;
	}
	if (InputHandler::pressed(binds::Pause))
	{
		TogglePaused();
	}
	if (paused)
	{
		planets[activePlanet].camera.SetView();
		return;
	}
	planets[activePlanet].Update(dt);
	toolHandler->Update(dt, &planets[activePlanet]);
}
void Game::Render()
{
	planets[activePlanet].Render();
}

Planet* Game::ActivePlanet()
{
	return &planets[activePlanet];
}