#include "Main.hpp"
#include "InputHandler.hpp"
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
	window->setFramerateLimit(120);
	//set the icon image that is displayed in the corner of the window
	sf::Image icon;
	icon.loadFromFile("resources/images/icon.png");
	window->setIcon(256, 256, icon.getPixelsPtr());

	std::vector<HitboxShape*> shapes;
	shapes.push_back(new HitboxCircle(sf::Vector2f(0.f, 0.f), 40.f));
	shapes.push_back(new HitboxRect(sf::Vector2f(200.f, 100.f), sf::Vector2f(50.f, 50.f)));
	shapes.push_back(new HitboxCircle(sf::Vector2f(450.f, 200.f), 200.f));
	while (window->isOpen())
	{
		InputHandler::ProcessEvents();

		window->clear(sf::Color::Black);
		shapes[0]->SetTransform(InputHandler::mousePos, sf::Vector2f(1.f, 1.f));
		for (uint i = 0; i < shapes.size(); i++)
		{
			shapes[i]->Display(shapes);
		}
		window->display();
	}
	return 0;
}
