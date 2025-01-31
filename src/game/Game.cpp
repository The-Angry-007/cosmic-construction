#include "Game.hpp"
#include "InputHandler.hpp"
#include "Main.hpp"
#include "RecipeHandler.hpp"
#include "binds.hpp"
Game::Game()
{
	paused = false;
	inMenu = false;
	planets = {};

	activePlanet = 0;
	planets.push_back(Planet(0));
	loadedTimer = 5;
	InputHandler::RemoveMbPressed(sf::Mouse::Button::Left);
	InputHandler::RemoveMbDown(sf::Mouse::Button::Left);
	toolHandler = new ToolHandler();
	updateClock.restart();
	numUpdates = 0;
	SaveHandler::saveTimer.restart();
}
Game::~Game()
{
}

void Game::NewGame()
{
	for (uint i = 0; i < planets.size(); i++)
	{
		planets[i].Init(false);
		sf::Clock timer;
		do
		{
			planets[i].Update(0.f);
		} while (timer.restart().asSeconds() > 0.0001f);
	}
	tutorial = new Tutorial();
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

	float timeSinceSave = SaveHandler::saveTimer.getElapsedTime().asSeconds();
	if (guihandler.settings->saveInterval != -1 && timeSinceSave > guihandler.settings->saveInterval * 60)
	{
		std::cout << "running autosave" << std::endl;
		SaveHandler::saveTimer.restart();
		SaveHandler::SaveGame();
	}
	if (loadedTimer > 0)
	{
		loadedTimer--;
		return;
	}
	if (InputHandler::pressed(binds::Pause) && !inMenu)
	{
		TogglePaused();
	}
	planets[activePlanet].camera.SetView();

	if (paused)
	{
		return;
	}
	RecipeHandler::Update(dt);
	if (!inMenu)
	{
		planets[activePlanet].Update(dt);
	}
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

void Game::WorldUpdate(float dt)
{
	if (paused)
	{
		return;
	}
	planets[activePlanet].WorldUpdate(dt);
}