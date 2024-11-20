#include "Main.hpp"
#include "InputHandler.hpp"
#include "gui.hpp"
#include "hitboxes.hpp"
#include "saving.hpp"
#include "utils.hpp"
#include <memory>

//a unique pointer to the window object; this is unique to prevent accidentally creating multiple windows
std::unique_ptr<sf::RenderWindow> window;
//width and height of the window
int width = 800;
int height = 500;

GUIHandler guihandler = GUIHandler();

void Print(std::vector<std::string> arr)
{
	std::cout << "[";
	for (uint i = 0; i < arr.size(); i++)
	{
		std::cout << '\"';
		std::cout << arr[i];
		std::cout << '\"';

		if (i < arr.size() - 1)
		{
			std::cout << ",";
		}
	}
	std::cout << "]";
}
void Print(std::vector<std::vector<std::string>> arr)
{
	std::cout << "[";
	for (uint i = 0; i < arr.size(); i++)
	{
		Print(arr[i]);
		if (i != arr.size() - 1)
		{
			std::cout << ",";
		}
	}
	std::cout << "]\n";
}

//the main procedure that runs the program
int main()
{
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

	std::vector<float> frameLengths;
	float lengthsSum = 0;
	//how many frames to average the framerate of, so its smoother and easier to read
	int numFrames = 60;
	sf::Clock deltaClock;
	GUILabel fpsLabel(sf::Vector2f(0.1f, 0.03f), sf::Vector2f(0.1f, 0.03f), "");
	fpsLabel.origin = sf::Vector2f(0.f, 0.f);

	guihandler.InitGUIS();
	SaveHandler::Init();
	std::string path = SaveHandler::RelToAbsolute("testFile.txt");

	SaveHandler::WriteData(path, "hello world\nmulti-line test");
	std::string data = SaveHandler::ReadData(path);
	std::cout << data << std::endl;
	deltaClock.restart();
	while (window->isOpen())
	{

		InputHandler::ProcessEvents();
		sf::View view(sf::FloatRect(0.f, 0.f, width, height));
		window->setView(view);
		float dt = deltaClock.restart().asSeconds();
		frameLengths.push_back(dt);
		lengthsSum += dt;
		if (frameLengths.size() > numFrames)
		{
			lengthsSum -= frameLengths[0];
			frameLengths.erase(frameLengths.begin());
		}
		int fps = (int)(1.f / (lengthsSum / frameLengths.size()));
		fpsLabel.value = std::to_string(fps) + " fps";
		guihandler.Update(dt);
		window->clear(sf::Color::Black);
		guihandler.Render();
		fpsLabel.Render();

		window->display();
	}
	return 0;
}
