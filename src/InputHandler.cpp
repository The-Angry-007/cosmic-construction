#include "InputHandler.hpp"
#include "Main.hpp"
#include "binds.hpp"
namespace InputHandler
{
std::vector<sf::Keyboard::Key> keysPressed;
std::vector<sf::Keyboard::Key> keysDown;
std::vector<sf::Keyboard::Key> keysReleased;

std::vector<sf::Mouse::Button> mouseButtonsPressed;
std::vector<sf::Mouse::Button> mouseButtonsDown;
std::vector<sf::Mouse::Button> mouseButtonsReleased;

sf::Vector2f mousePos(0, 0);
sf::Vector2f guiMP(0, 0);
sf::Vector2f scroll(0, 0);
std::string typedText = "";
bool mouseIsBlocked = false;

int oldWidth = width;
int oldHeight = height;
bool isFullscreen = false;
};

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

bool InputHandler::keyDown(sf::Keyboard::Key key)
{
	return getIndex(keysDown, key) != -1;
}

bool InputHandler::keyPressed(sf::Keyboard::Key key)
{
	return getIndex(keysPressed, key) != -1;
}

bool InputHandler::keyReleased(sf::Keyboard::Key key)
{
	return getIndex(keysReleased, key) != -1;
}

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
	while (window->pollEvent(event))
	{
		if (event.type == event.Closed)
		{
			window->close();
			exit(0);
		}
		else if (event.type == event.KeyPressed)
		{
			//only add to pressed and down if not already in down
			if (getIndex(keysDown, event.key.code) == -1)
			{
				keysDown.push_back(event.key.code);
				keysPressed.push_back(event.key.code);
			}
		}
		else if (event.type == event.KeyReleased)
		{
			//remove from keys down
			int index = getIndex(keysDown, event.key.code);
			if (index != -1)
			{
				keysDown.erase(keysDown.begin() + index);
				keysReleased.push_back(event.key.code);
			}
		}
		else if (event.type == event.MouseButtonPressed)
		{
			//same as 2 conditions above, but for mouse buttons
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
		else if (event.type == event.TextEntered)
		{
			typedText += event.text.unicode;
		}
		else if (event.type == event.MouseWheelMoved)
		{
			scroll.y = event.mouseWheel.delta;
		}
		else if (event.type == event.Resized)
		{
			width = window->getSize().x;
			height = window->getSize().y;
		}
	}
	mousePos = (sf::Vector2f)sf::Mouse::getPosition(*window);
	guiMP = sf::Vector2f(mousePos.x / width, mousePos.y / height);
	//do fullscreen changing
	if (pressed(binds::Fullscreen))
	{
		isFullscreen = !isFullscreen;
		int style;
		window->close();
		sf::VideoMode v(width, height);
		if (isFullscreen)
		{
			oldWidth = width;
			oldHeight = height;
			style = sf::Style::Fullscreen;
			v = sf::VideoMode::getFullscreenModes()[0];
		}
		else
		{
			width = oldWidth;
			height = oldHeight;
			style = sf::Style::Default;
			v = sf::VideoMode(width, height);
		}
		window->create(v, "Cosmic Construction", style);
		int fr = guihandler.settings->framerate;
		if (fr == -1)
		{
			window->setFramerateLimit(1000);
			window->setVerticalSyncEnabled(true);
		}
		else
		{
			window->setFramerateLimit(fr);
		}
		sf::Image icon;
		icon.loadFromFile("resources/images/icon.png");
		window->setIcon(256, 256, icon.getPixelsPtr());
	}
}

void InputHandler::RemoveKeyDown(sf::Keyboard::Key key)
{
	int index = getIndex(keysDown, key);
	keysDown.erase(keysDown.begin() + index);
}
void InputHandler::RemoveKeyPressed(sf::Keyboard::Key key)
{
	int index = getIndex(keysPressed, key);
	keysPressed.erase(keysPressed.begin() + index);
}
void InputHandler::RemoveKeyReleased(sf::Keyboard::Key key)
{
	int index = getIndex(keysReleased, key);
	keysReleased.erase(keysReleased.begin() + index);
}
void InputHandler::RemoveMbDown(sf::Mouse::Button button)
{
	int index = getIndex(mouseButtonsDown, button);
	mouseButtonsDown.erase(mouseButtonsDown.begin() + index);
}
void InputHandler::RemoveMbPressed(sf::Mouse::Button button)
{
	int index = getIndex(mouseButtonsPressed, button);
	mouseButtonsPressed.erase(mouseButtonsPressed.begin() + index);
}
void InputHandler::RemoveMbReleased(sf::Mouse::Button button)
{
	int index = getIndex(mouseButtonsReleased, button);
	mouseButtonsReleased.erase(mouseButtonsReleased.begin() + index);
}

bool InputHandler::pressed(int code)
{
	if (code > 0)
	{
		return keyPressed(static_cast<sf::Keyboard::Key>(code - 1));
	}
	else
	{
		return mbPressed(static_cast<sf::Mouse::Button>(-code - 1));
	}
}

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