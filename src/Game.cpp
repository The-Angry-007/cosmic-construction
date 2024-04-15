#include "Game.hpp"
#include "Item.hpp"
#include "Main.hpp"
#include "SaveHandler.hpp"
#include "inputHandler.hpp"
Game::Game()
{
	gravity = 9.81f * 16.f;
	//green grass color
	camera.SetBgCol(sf::Color(89, 149, 48));
}
void Game::NewGame()
{
	items.push_back(Item(sf::Vector2f(0.f, 0.f), 16.f, 0, 1));
}
void Game::Init(bool newGame)
{
	this->savePath = SaveHandler::workingDir;
	paused = false;
	timePassed = new sf::Clock();
	if (newGame)
	{
		NewGame();
	}
	else
	{
		NewGame();
		//SaveHandler::LoadGame();
	}
}
void Game::Update(double dt)
{
	if (inp.keyPressed(sf::Keyboard::Key::Escape))
	{
		TogglePaused();
	}
	if (paused)
	{
		return;
	}
	for (uint i = 0; i < items.size(); i++)
	{
		items[i].Update(dt);
	}
}
void Game::TogglePaused()
{
	if (!paused)
	{
		paused = true;
		menu.OpenMenu(5);
	}
	else
	{
		paused = false;
		menu.OpenMenu(4);
	}
}
void Game::Render()
{
	timer.TimeFunc("camera draw bg", false);
	camera.RenderBg();
	timer.end();
	for (uint i = 0; i < items.size(); i++)
	{
		items[i].Render();
	}
}
Game::~Game()
{
}
