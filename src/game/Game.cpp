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
		//this forces the planet to keep updating until all the starting chunks have been generated
		do
		{
			planets[i].Update(0.f);
		} while (timer.restart().asSeconds() > 0.0001f);
	}
	//initialises the tutorial
	tutorial = new Tutorial();
}
void Game::TogglePaused()
{
	//if now paused then open pause menu, otherwise close it
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
//load in planets
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
	//check if autosave needs to be completed
	float timeSinceSave = SaveHandler::saveTimer.getElapsedTime().asSeconds();
	//save interval of -1 indicates autosave should never happen
	if (guihandler.settings->saveInterval != -1 && timeSinceSave > guihandler.settings->saveInterval * 60)
	{
		//restart save timer
		SaveHandler::saveTimer.restart();
		SaveHandler::SaveGame();
	}
	//prevents the game from updating for 5 frames after being loaded in (visual glitches happen otherwise)
	if (loadedTimer > 0)
	{
		loadedTimer--;
		return;
	}
	//toggle paused if pause button pressed
	if (InputHandler::pressed(binds::Pause) && !inMenu)
	{
		TogglePaused();
	}
	//update camera view
	planets[activePlanet].camera.SetView();

	if (paused)
	{
		return;
	}
	//update planet, recipe visuals and toolhandler
	RecipeHandler::Update(dt);
	if (!inMenu)
	{
		planets[activePlanet].Update(dt);
	}
	toolHandler->Update(dt, &planets[activePlanet]);
}
void Game::Render()
{
	//render active planet
	planets[activePlanet].Render();
}

Planet* Game::ActivePlanet()
{
	return &planets[activePlanet];
}
//calls world update for active planet; this is where structures and items are updated and has a fixed delta time
void Game::WorldUpdate(float dt)
{
	if (paused)
	{
		return;
	}
	planets[activePlanet].WorldUpdate(dt);
}