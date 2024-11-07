#include "Main.hpp"
#include "InputHandler.hpp"
#include "hitboxes/HitboxRect.hpp"
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
	window->setFramerateLimit(120);
	//set the icon image that is displayed in the corner of the window
	sf::Image icon;
	icon.loadFromFile("resources/images/icon.png");
	window->setIcon(256, 256, icon.getPixelsPtr());

	//rect in middle of screen, 100px away from edges
	HitboxRect rect(sf::Vector2f(400.f, 250.f), sf::Vector2f(300.f, 150.f));
	//rect that will be following the mouse
	HitboxRect rect2(sf::Vector2f(0.f, 0.f), sf::Vector2f(20.f, 20.f));
	while (window->isOpen())
	{
		InputHandler::ProcessEvents();

		window->clear(sf::Color::Black);
		//set transform to position of mouse
		rect2.SetTransform(InputHandler::mousePos, sf::Vector2f(1.f, 1.f));
		rect2.Display(&rect);
		rect.Display(&rect2);
		window->display();
	}
	return 0;
}
