#include "Main.hpp"
#include "InputHandler.hpp"
#include <memory>

//a unique pointer to the window object; this is unique to prevent accidentally creating multiple windows
std::unique_ptr<sf::RenderWindow> window;
//width and height of the window
int width, height;

//the main procedure that runs the program
int main()
{
	//initialise the window object
	window = std::make_unique<sf::RenderWindow>();
	//make a 800x500 window with the title "Cosmic Construction"
	window->create(sf::VideoMode(800.0f, 500.0f), "Cosmic Construction");
	window->setFramerateLimit(3);
	//set the icon image that is displayed in the corner of the window
	sf::Image icon;
	icon.loadFromFile("resources/images/icon.png");
	window->setIcon(256, 256, icon.getPixelsPtr());
	std::string typedText;
	while (window->isOpen())
	{
		window->clear(sf::Color::Black);
		InputHandler::ProcessEvents();
		typedText += InputHandler::typedText;
		std::cout << typedText << std::endl;
		window->display();
	}
	return 0;
}
