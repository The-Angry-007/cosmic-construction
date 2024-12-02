#include "Game.hpp"
#include "InputHandler.hpp"
#include "Main.hpp"
#include "binds.hpp"
Game::Game()
{
	paused = false;
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
		return;
	}
}
void Game::Render()
{
	//draw green background for testing
	sf::RectangleShape r(sf::Vector2f(width, height));
	r.setFillColor(sf::Color(100, 255, 100));
	window->draw(r);
}