#include "Game.hpp"
#include "InputHandler.hpp"
#include "Main.hpp"
#include "binds.hpp"
Game::Game()
{
	paused = false;
	item = new Item(sf::Vector2f(0.f, 0.f));
	// item = new Item(sf::Vector2f(rand() % width, rand() % height));
	camera = new Camera(sf::Vector2f(0.f, 0.f), 1.f);
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
	camera->Update(dt);
	item->Update(dt);
}
void Game::Render()
{
	item->Render();
}