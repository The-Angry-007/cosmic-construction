#include "Include.hpp"
#ifndef M_PI
	#define M_PI 3.14159265358979323846
#endif

#include <math.h>

sf::RenderWindow* window = new sf::RenderWindow();
sf::Clock deltaClock;
//Gui gui;
InputHandler inp;
sf::Font* defaultFont = new sf::Font();
sf::Font* pixelFont = new sf::Font();
int width, height;
Menu menu;
Game* game = nullptr;
bool debug = false;
Timer timer;
Camera camera(sf::Vector2f(0.f, 0.f), 1.f);
int main()
{
	SaveHandler::ResetDir();
	util::Platform platform;
	// in Windows at least, this must be called before creating the window
	float screenScalingFactor = platform.getScreenScalingFactor(window->getSystemHandle());
	// Use the screenScalingFactor
	window->create(sf::VideoMode(800.0f * screenScalingFactor, 500.0f * screenScalingFactor), "Cosmic Construction");
	// window->setVerticalSyncEnabled(false);
	window->setFramerateLimit(200);
	sf::Image icon;
	icon.loadFromFile("resources/images/icon.png");
	window->setIcon(256, 256, icon.getPixelsPtr());
	if (!defaultFont->loadFromFile("resources/fonts/RobotoMono-Regular.ttf"))
	{
		window->close();
	}
	if (!pixelFont->loadFromFile("resources/fonts/pixel.ttf"))
	{
		window->close();
	}

	//defaultFont = pixelFont;
	//gui.Init();

	InitItems();
	menu = InitMenu();
	camera.Update();
	deltaClock.restart();
	if (debug)
	{
		menu.OpenMenu(3);
		menu.slots[0].onClick();
	}
	while (window->isOpen())
	{
		timer.TimeFunc("whole frame", false);
		timer.TimeFunc("whole update", true);
		timer.TimeFunc("input events", true);
		inp.ProcessEvents();
		timer.end();
		timer.nFrames++;

		double dt = deltaClock.restart().asSeconds();

		if (game != nullptr)
		{
			game->Update(dt);
		}
		timer.TimeFunc("camera update", true);
		camera.Update();
		timer.end();
		timer.TimeFunc("menu update", true);
		menu.Update(dt);
		timer.end();
		timer.end();
		timer.TimeFunc("whole render", false);
		window->clear(sf::Color(8, 0, 20));
		timer.TimeFunc("game render", false);
		if (game != nullptr)
		{
			game->Render();
		}
		timer.end();
		timer.TimeFunc("render menu", false);
		camera.RenderMenu(&menu, dt);
		timer.end();
		timer.TimeFunc("display window", false);
		window->display();
		timer.end();
		timer.end();
		timer.end();
		if (inp.keyDown(sf::Keyboard::LControl) && inp.keyPressed(sf::Keyboard::Key::T))
		{
			if (!timer.timing)
			{
				timer.StartTiming();
			}
			else
			{
				timer.EndTiming();
			}
		}
	}
	return 0;
}
