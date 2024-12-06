#include "Game.hpp"
#include "InputHandler.hpp"
#include "Main.hpp"
#include "binds.hpp"
Game::Game()
{
	paused = false;
	planets = {};
	planets.push_back(Planet(0));
	planets.push_back(Planet(1));
	activePlanet = 0;
}
Game::~Game()
{
}

void Game::NewGame()
{
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
}
void Game::Update(float dt)
{

	if (InputHandler::pressed(binds::Pause))
	{
		TogglePaused();
	}
	if (paused)
	{
		planets[activePlanet].camera.SetView();
		return;
	}
	if (InputHandler::keyPressed(sf::Keyboard::Key::Right))
	{
		activePlanet++;
		if (activePlanet >= planets.size())
		{
			activePlanet = 0;
		}
	}
	planets[activePlanet].Update(dt);
}
void Game::Render()
{
	planets[activePlanet].Render();
}