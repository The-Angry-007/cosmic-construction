#include "Main.hpp"
#include "InputHandler.hpp"
#include "gui.hpp"
#include "hitboxes.hpp"
#include "saving.hpp"
#include "utils.hpp"

//a unique pointer to the window object; this is unique to prevent accidentally creating multiple windows
std::unique_ptr<sf::RenderWindow> window;
//width and height of the window
int width = 800;
int height = 500;

GUIHandler guihandler = GUIHandler();

Game* game = nullptr;

//the main procedure that runs the program
int main()
{
	//initialise save handler
	SaveHandler::Init();
	//initialise the random number generator (for scrolling galaxy)
	srand(time(NULL));
	//initialise the window object
	window = std::make_unique<sf::RenderWindow>();
	//make a 800x500 window with the title "Cosmic Construction"
	window->create(sf::VideoMode(width, height), "Cosmic Construction");
	window->setFramerateLimit(1000);
	window->setVerticalSyncEnabled(true);
	//set the icon image that is displayed in the corner of the window
	sf::Image icon;
	icon.loadFromFile("resources/images/icon.png");
	window->setIcon(256, 256, icon.getPixelsPtr());

	//make the window black while loading
	window->clear(sf::Color::Black);
	window->display();

	sf::Clock deltaClock;
	//label to display fps
	GUILabel fpsLabel(sf::Vector2f(0.1f, 0.03f), sf::Vector2f(0.1f, 0.03f), "");
	fpsLabel.origin = sf::Vector2f(0.f, 0.f);
	//construct the interfaces
	guihandler.InitGUIS();

	deltaClock.restart();
	//main loop: runs once for each frame
	while (window->isOpen())
	{

		InputHandler::ProcessEvents();
		//adjust the window's view to match the window's dimensions
		sf::View view(sf::FloatRect(0.f, 0.f, width, height));
		window->setView(view);
		//calculate delta time (time passed since last frame)
		float dt = deltaClock.restart().asSeconds();

		/* ---UPDATE--- */
		guihandler.Update(dt);
		if (game != nullptr)
		{
			game->Update(dt);
		}

		/* ---RENDER--- */
		//reset contents of window
		window->clear(sf::Color::Black);
		if (game != nullptr)
		{
			game->Render();
		}

		guihandler.Render();

		//display window
		window->display();
	}
	return 0;
}
