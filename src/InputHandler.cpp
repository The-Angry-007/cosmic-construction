#include "InputHandler.hpp"

namespace InputHandler
{
std::vector<sf::Keyboard::Key> keysPressed;
std::vector<sf::Keyboard::Key> keysDown;
std::vector<sf::Keyboard::Key> keysReleased;

std::vector<sf::Mouse::Button> mouseButtonsPressed;
std::vector<sf::Mouse::Button> mouseButtonsDown;
std::vector<sf::Mouse::Button> mouseButtonsReleased;

sf::Vector2f mousePos(0, 0);
sf::Vector2f scroll(0, 0);
std::string typedText = "";
bool mouseIsBlocked = false;
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
