#include "Game.hpp"
#include "InputHandler.hpp"
#include "Main.hpp"
#include "binds.hpp"
Game::Game()
{
	paused = false;
	int numItems = 10;
	items = {};
	for (uint i = 0; i < numItems; i++)
	{
		int size = 100;
		items.push_back(new Item(sf::Vector2f(rand() % (size * 2) - size, rand() % (size * 2) - size)));
	}
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
		camera->SetView();
		return;
	}
	camera->Update(dt);
	for (uint i = 0; i < items.size(); i++)
	{
		items[i]->Update(dt);
	}
}
void Game::Render()
{
	for (uint i = 0; i < items.size(); i++)
	{
		items[i]->Render();
	}
}