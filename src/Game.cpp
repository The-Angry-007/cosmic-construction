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
	mouseDragsItems = true;
}
void Game::NewGame()
{
	for (int i = 0; i < 100; i++)
	{
		items.push_back(Item(sf::Vector2f(rand() % 100 - 50, rand() % 100 - 50), rand() % 3, 13));
	}
	items.push_back(Item(sf::Vector2f(0.f, 0.f), 0, 1));
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
		//NewGame();
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
	timer.TimeFunc("mouse suck", true);
	sf::Vector2f mouseWorldPos = window->mapPixelToCoords((sf::Vector2i)inp.mousePos);
	if (inp.mbDown(sf::Mouse::Button::Left))
	{
		for (uint i = 0; i < items.size(); i++)
		{
			sf::Vector2f o = mouseWorldPos - items[i].pos;
			float sqrDist = (o.x * o.x) + (o.y * o.y);
			if (sqrDist < 256)
			{
				sqrDist = 256;
			}
			float mag = 5000.f;
			float force = mag / sqrDist;
			float vel = force * dt;
			items[i].vel += sf::Vector2f(vel * o.x, vel * o.y);
		}
	}
	timer.end();
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
	timer.TimeFunc("render items", false);
	for (uint i = 0; i < items.size(); i++)
	{
		items[i].Render();
	}
	timer.end();
}
Game::~Game()
{
}
