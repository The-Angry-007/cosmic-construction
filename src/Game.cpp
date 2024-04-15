#include "Game.hpp"
#include "Main.hpp"
#include "SaveHandler.hpp"
#include "inputHandler.hpp"
Game::Game()
{
	//green grass color
	camera.SetBgCol(sf::Color(89, 149, 48));
}
void Game::NewGame()
{
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
		SaveHandler::LoadGame();
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
}
Game::~Game()
{
}
