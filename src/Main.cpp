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

	//used to caclulate the average framerate over the past few frames
	std::vector<float> frameLengths;
	float lengthsSum = 0;
	//how many frames to average the framerate of, so its smoother and easier to read
	int numFrames = 60;
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
		frameLengths.push_back(dt);
		lengthsSum += dt;
		//trim framelengths if too many are stored
		if (frameLengths.size() > numFrames)
		{
			lengthsSum -= frameLengths[0];
			frameLengths.erase(frameLengths.begin());
		}
		//calculate the avg fps as an integer
		int fps = (int)(1.f / (lengthsSum / frameLengths.size()));
		fpsLabel.value = std::to_string(fps) + " fps";
		/* ---UPDATE--- */
		std::cout << "started updating gui" << std::endl;
		guihandler.Update(dt);
		std::cout << "finished updating gui" << std::endl;
		if (game != nullptr)
		{
			std::cout << "updating game" << std::endl;
			game->Update(dt);
		}
		std::cout << "finished update" << std::endl;

		/* ---RENDER--- */
		//reset contents of window
		window->clear(sf::Color::Black);
		if (game != nullptr)
		{
			std::cout << "rendering game" << std::endl;
			game->Render();
		}
		std::cout << "about to render" << std::endl;

		guihandler.Render();
		fpsLabel.Render();
		std::cout << "finished render" << std::endl;

		//display window
		window->display();
	}
	return 0;
}
