#include "Include.hpp"
Game::Game()
{
	gravity = 9.81f * 16.f;
	//green grass color
	camera.SetBgCol(sf::Color(89, 149, 48));
	mouseDragsItems = true;
}
void Game::NewGame()
{
	for (int i = 0; i < 100000; i++)
	{
		items.push_back(Item(sf::Vector2f(rand() % 100 - 50, rand() % 100 - 50), rand() % 3));
	}
	items.push_back(Item(sf::Vector2f(1.f, 0.f), 0));
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
	this->ItemVertices = sf::VertexArray(sf::Triangles, this->items.size() * 6);
	for (uint i = 0; i < items.size(); i++)
	{
		uint j = i * 6;
		sf::Vector2f topLeft(texturePoses[items[i].id].x, texturePoses[items[i].id].y);
		uint size = items[i].size;
		ItemVertices[j].texCoords = topLeft;
		ItemVertices[j + 1].texCoords = sf::Vector2f(topLeft.x + size, topLeft.y);
		ItemVertices[j + 2].texCoords = sf::Vector2f(topLeft.x, topLeft.y + size);
		ItemVertices[j + 3].texCoords = sf::Vector2f(topLeft.x, topLeft.y + size);
		ItemVertices[j + 4].texCoords = sf::Vector2f(topLeft.x + size, topLeft.y);
		ItemVertices[j + 5].texCoords = sf::Vector2f(topLeft.x + size, topLeft.y + size);
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
	timer.TimeFunc("update items", true);
	for (uint i = 0; i < items.size(); i++)
	{

		items[i].Update(dt);
	}
	timer.end();
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
	// sf::VertexArray v = *this->ItemVertices;
	for (uint i = 0; i < items.size(); i++)
	{
		uint j = i * 6;
		sf::Vector2f halfSizex(0, items[i].size / 2.f);
		sf::Vector2f halfSizey(items[i].size / 2.f, 0);
		sf::Vector2f halfSize = halfSizex + halfSizey;
		sf::Vector2f mid = items[i].pos;
		ItemVertices[j].position = mid - halfSize;
		ItemVertices[j + 1].position = mid - halfSizey + halfSizex;
		ItemVertices[j + 2].position = mid + halfSizey - halfSizex;
		ItemVertices[j + 3].position = mid + halfSizey - halfSizex;
		ItemVertices[j + 4].position = mid - halfSizey + halfSizex;
		ItemVertices[j + 5].position = mid + halfSizey + halfSizex;
	}
	window->draw(ItemVertices, &itemTextureAtlas);
	timer.end();
}
Game::~Game()
{
}
