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
	srand(time(NULL));
	//initialise the window object
	window = std::make_unique<sf::RenderWindow>();
	//make a 800x500 window with the title "Cosmic Construction"
	window->create(sf::VideoMode(width, height), "Cosmic Construction");
	window->setFramerateLimit(120);
	//set the icon image that is displayed in the corner of the window
	sf::Image icon;
	icon.loadFromFile("resources/images/icon.png");
	window->setIcon(256, 256, icon.getPixelsPtr());

	std::vector<float> frameLengths;
	float lengthsSum = 0;
	//how many frames to average the framerate of, so its smoother and easier to read
	int numFrames = 60;
	sf::Clock deltaClock;
	GUILabel fpsLabel(sf::Vector2f(0.1f, 0.05f), sf::Vector2f(0.1f, 0.05f), "");
	fpsLabel.origin = sf::Vector2f(0.f, 0.f);
	GUIPanel p(sf::Vector2f(0, 0), sf::Vector2f(0.5f, 0.1f), sf::Color(100, 100, 100));
	GUIPanel p2(sf::Vector2f(0, 0), sf::Vector2f(0.5f, 0.1f), sf::Color(150, 150, 150));
	GUIPanel p3(sf::Vector2f(0, 0), sf::Vector2f(0.1f, 0.15f), sf::Color(255, 255, 255));
	GUISlider s(sf::Vector2f(0.5f, 0.5f), sf::Vector2f(0.3f, 0.1f), &p3, &p, &p2);
	deltaClock.restart();
	while (window->isOpen())
	{
		sf::View view(sf::FloatRect(0.f, 0.f, width, height));
		window->setView(view);
		InputHandler::ProcessEvents();
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
		s.Update(dt);
		window->clear(sf::Color::Black);
		s.Render();
		fpsLabel.Render();
		window->display();
	}
	return 0;
}
