#include "Main.hpp"
#include "InputHandler.hpp"
#include "gui/gui.hpp"
#include "hitboxes/Hitboxes.hpp"
#include <memory>

//a unique pointer to the window object; this is unique to prevent accidentally creating multiple windows
std::unique_ptr<sf::RenderWindow> window;
//width and height of the window
int width = 800;
int height = 500;

//the main procedure that runs the program
int main()
{
	//initialise the window object
	window = std::make_unique<sf::RenderWindow>();
	//make a 800x500 window with the title "Cosmic Construction"
	window->create(sf::VideoMode(width, height), "Cosmic Construction");
	window->setFramerateLimit(30);
	//set the icon image that is displayed in the corner of the window
	sf::Image icon;
	icon.loadFromFile("resources/images/icon.png");
	window->setIcon(256, 256, icon.getPixelsPtr());

	GUIPanel panel(sf::Vector2f(0.5f, 0.5f), sf::Vector2f(0.4f, 0.4f), sf::Color::White);
	panel.blocksMouseInput = true;
	while (window->isOpen())
	{
		InputHandler::ProcessEvents();
		window->clear(sf::Color::Black);
		//mouse position scaled to be between 0 and 1
		if (panel.isClicked())
		{
			panel.SetColor(sf::Color::Green);
		}
		else
		{
			panel.SetColor(sf::Color::Red);
		}
		panel.Render();
		window->display();
	}
	return 0;
}
