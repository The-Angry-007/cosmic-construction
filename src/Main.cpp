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
	Hitbox* hitbox1 = new Hitbox(sf::Vector2f(100.f, 100.f), sf::Vector2f(1.f, 1.f));
	hitbox1->AddShape(new HitboxRect(sf::Vector2f(0.f, 0.f), sf::Vector2f(50.f, 50.f)));
	hitbox1->AddShape(new HitboxCircle(sf::Vector2f(50.f, 0.f), 50.f));
	Hitbox* hitbox2 = new Hitbox(sf::Vector2f(0.f, 0.f), sf::Vector2f(1.f, 1.f));
	hitbox2->AddShape(new HitboxRect(sf::Vector2f(0.f, 0.f), sf::Vector2f(20.f, 20.f)));
	hitbox2->AddShape(new HitboxCircle(sf::Vector2f(-20.f, 0.f), 20.f));
	hitbox2->AddShape(new HitboxCircle(sf::Vector2f(20.f, 0.f), 20.f));
	while (window->isOpen())
	{
		InputHandler::ProcessEvents();
		hitbox2->SetTransform(InputHandler::mousePos, sf::Vector2f(1.f, 1.f));
		window->clear(sf::Color::Black);
		hitbox2->Display(std::vector<Hitbox*> { hitbox1 });
		hitbox1->Display(std::vector<Hitbox*> { hitbox2 });

		window->display();
	}
	delete hitbox1;
	delete hitbox2;
	return 0;
}
