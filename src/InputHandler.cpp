#include "InputHandler.hpp"
#include "Main.hpp"
#include "binds.hpp"
//declare all the variables
namespace InputHandler
{
std::vector<sf::Keyboard::Key> keysPressed;
std::vector<sf::Keyboard::Key> keysDown;
std::vector<sf::Keyboard::Key> keysReleased;

std::vector<sf::Mouse::Button> mouseButtonsPressed;
std::vector<sf::Mouse::Button> mouseButtonsDown;
std::vector<sf::Mouse::Button> mouseButtonsReleased;

sf::Vector2f mousePos(0, 0);
//mouse position scaled between 0 and 1, to check collisions with GUI objects
sf::Vector2f guiMP(0, 0);
//mouse scroll that frame
sf::Vector2f scroll(0, 0);
//any text typed that frame (accounts for caps lock etc)
std::string typedText = "";
//whether the mouse is blocked by gui
bool mouseIsBlocked = false;

//for storing the window size before switching to fullscreen
int oldWidth = width;
int oldHeight = height;
bool isFullscreen = false;
};
//linear search to find the index of a key within a list of keys
int InputHandler::getIndex(std::vector<sf::Keyboard::Key> keys, sf::Keyboard::Key key)
{
	for (uint i = 0; i < keys.size(); i++)
	{
		if (keys[i] == key)
		{
			return i;
		}
	}
	return -1;
}
//same as algorithm above, but for mouse buttons
int InputHandler::getIndex(std::vector<sf::Mouse::Button> buttons, sf::Mouse::Button button)
{
	for (uint i = 0; i < buttons.size(); i++)
	{
		if (buttons[i] == button)
		{
			return i;
		}
	}
	return -1;
}
//returns true for every frame a key is pressed down
bool InputHandler::keyDown(sf::Keyboard::Key key)
{
	return getIndex(keysDown, key) != -1;
}
//returns true for the frame the key goes from not being pressed to being pressed
bool InputHandler::keyPressed(sf::Keyboard::Key key)
{
	return getIndex(keysPressed, key) != -1;
}
//returns true for the frame the key goes from being pressed to not pressed
bool InputHandler::keyReleased(sf::Keyboard::Key key)
{
	return getIndex(keysReleased, key) != -1;
}

//mouse button equivalents of the functions above
bool InputHandler::mbDown(sf::Mouse::Button button)
{
	return getIndex(mouseButtonsDown, button) != -1;
}

bool InputHandler::mbPressed(sf::Mouse::Button button)
{
	return getIndex(mouseButtonsPressed, button) != -1;
}

bool InputHandler::mbReleased(sf::Mouse::Button button)
{
	return getIndex(mouseButtonsReleased, button) != -1;
}

//the function called at the start of every frame. deals with all events given by SFML
void InputHandler::ProcessEvents()
{
	//reset the keys pressed and released, same with mouse buttons
	keysPressed = {};
	keysReleased = {};
	mouseButtonsPressed = {};
	mouseButtonsReleased = {};
	//reset typed text, scroll and mouseIsBlocked status
	typedText = "";
	scroll = sf::Vector2f(0, 0);
	mouseIsBlocked = false;
	sf::Event event;
	//run this for each new event that happened this frame
	while (window->pollEvent(event))
	{
		//if the event is the close button in the corner of the window was clicked, end the program
		if (event.type == event.Closed)
		{
			window->close();
			exit(0);
		}
		//if the event is a key was pressed
		else if (event.type == event.KeyPressed)
		{
			//only add to pressed and down if not already in down
			if (getIndex(keysDown, event.key.code) == -1)
			{
				keysDown.push_back(event.key.code);
				keysPressed.push_back(event.key.code);
			}
		}
		//if the event was a key released
		else if (event.type == event.KeyReleased)
		{
			//remove from keys down if it is in there
			int index = getIndex(keysDown, event.key.code);
			if (index != -1)
			{
				keysDown.erase(keysDown.begin() + index);
				keysReleased.push_back(event.key.code);
			}
		}
		//same as 2 conditions above, but for mouse buttons
		else if (event.type == event.MouseButtonPressed)
		{
			if (getIndex(mouseButtonsDown, event.mouseButton.button) == -1)
			{
				mouseButtonsDown.push_back(event.mouseButton.button);
				mouseButtonsPressed.push_back(event.mouseButton.button);
			}
		}
		else if (event.type == event.MouseButtonReleased)
		{
			int index = getIndex(mouseButtonsDown, event.mouseButton.button);
			if (index != -1)
			{
				mouseButtonsDown.erase(mouseButtonsDown.begin() + index);
				mouseButtonsReleased.push_back(event.mouseButton.button);
			}
		}
		//the character typed in this event is appended to the typed text string
		else if (event.type == event.TextEntered)
		{
			typedText += event.text.unicode;
		}
		//update scroll
		else if (event.type == event.MouseWheelMoved)
		{
			scroll.y = event.mouseWheel.delta;
		}
		//if window is resized, set width and height to new size
		else if (event.type == event.Resized)
		{
			width = window->getSize().x;
			height = window->getSize().y;
		}
	}
	//get the mouse position relative to the window
	mousePos = (sf::Vector2f)sf::Mouse::getPosition(*window);
	//scale the gui mouse pos to be between 0 and 1
	guiMP = sf::Vector2f(mousePos.x / width, mousePos.y / height);
	//do fullscreen changing
	if (pressed(binds::Fullscreen))
	{
		//reverse the boolean
		isFullscreen = !isFullscreen;
		//style defines whether the mode is fullscreen or not
		int style;
		//close the current window
		window->close();
		sf::VideoMode v(width, height);
		//if fullscreen, store current width and height and set style to fullscreen
		if (isFullscreen)
		{
			oldWidth = width;
			oldHeight = height;
			style = sf::Style::Fullscreen;
			v = sf::VideoMode::getFullscreenModes()[0];
		}
		//otherwise reset the width and height and set the style to default
		else
		{
			width = oldWidth;
			height = oldHeight;
			style = sf::Style::Default;
			v = sf::VideoMode(width, height);
		}
		//create the window replacement
		window->create(v, "Cosmic Construction", style);
		//adjust width and height
		width = window->getSize().x;
		height = window->getSize().y;
		//get the framerate from the settings menu
		int fr = guihandler.settings->framerate;
		//framerate of -1 indicates vsync so account for this
		if (fr == -1)
		{
			window->setFramerateLimit(1000);
			window->setVerticalSyncEnabled(true);
		}
		else
		{
			window->setFramerateLimit(fr);
		}
		//set the icon of the window
		sf::Image icon;
		icon.loadFromFile("resources/images/icon.png");
		window->setIcon(256, 256, icon.getPixelsPtr());
	}
}
//find the index of the key to remove and remove it
void InputHandler::RemoveKeyDown(sf::Keyboard::Key key)
{
	int index = getIndex(keysDown, key);
	keysDown.erase(keysDown.begin() + index);
}
//same as above
void InputHandler::RemoveKeyPressed(sf::Keyboard::Key key)
{
	int index = getIndex(keysPressed, key);
	keysPressed.erase(keysPressed.begin() + index);
}
//same as above
void InputHandler::RemoveKeyReleased(sf::Keyboard::Key key)
{
	int index = getIndex(keysReleased, key);
	keysReleased.erase(keysReleased.begin() + index);
}
//same as above
void InputHandler::RemoveMbDown(sf::Mouse::Button button)
{
	int index = getIndex(mouseButtonsDown, button);
	mouseButtonsDown.erase(mouseButtonsDown.begin() + index);
}
//same as above
void InputHandler::RemoveMbPressed(sf::Mouse::Button button)
{
	int index = getIndex(mouseButtonsPressed, button);
	mouseButtonsPressed.erase(mouseButtonsPressed.begin() + index);
}
//same as above
void InputHandler::RemoveMbReleased(sf::Mouse::Button button)
{
	int index = getIndex(mouseButtonsReleased, button);
	mouseButtonsReleased.erase(mouseButtonsReleased.begin() + index);
}

//takes a code that can be negative for mouse buttons, positive for keyboard keys and returns whether it is pressed
//this is to work with the keybind system
bool InputHandler::pressed(int code)
{
	if (code > 0)
	{
		//convert it to a keyboard key enum
		return keyPressed(static_cast<sf::Keyboard::Key>(code - 1));
	}
	else
	{
		return mbPressed(static_cast<sf::Mouse::Button>(-code - 1));
	}
}
//same as above
bool InputHandler::down(int code)
{
	if (code > 0)
	{
		return keyDown(static_cast<sf::Keyboard::Key>(code - 1));
	}
	else
	{
		return mbDown(static_cast<sf::Mouse::Button>(-code - 1));
	}
}
//same as above
bool InputHandler::released(int code)
{
	if (code > 0)
	{
		return keyReleased(static_cast<sf::Keyboard::Key>(code - 1));
	}
	else
	{
		return mbReleased(static_cast<sf::Mouse::Button>(-code - 1));
	}
}
//same as other remove functions but for bind codes
void InputHandler::RemovePressed(int code)
{
	if (code > 0)
	{
		RemoveKeyPressed(static_cast<sf::Keyboard::Key>(code - 1));
	}
	else
	{
		RemoveMbPressed(static_cast<sf::Mouse::Button>(-code - 1));
	}
}
//same as above
void InputHandler::RemoveDown(int code)
{
	if (code > 0)
	{
		RemoveKeyDown(static_cast<sf::Keyboard::Key>(code - 1));
	}
	else
	{
		RemoveMbDown(static_cast<sf::Mouse::Button>(-code - 1));
	}
}
//same as above
void InputHandler::RemoveReleased(int code)
{
	if (code > 0)
	{
		RemoveKeyReleased(static_cast<sf::Keyboard::Key>(code - 1));
	}
	else
	{
		RemoveMbReleased(static_cast<sf::Mouse::Button>(-code - 1));
	}
}