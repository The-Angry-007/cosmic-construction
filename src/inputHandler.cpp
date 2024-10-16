#include "Include.hpp"
InputHandler::InputHandler()
{
	isFullScreen = false;
}
void InputHandler::ProcessEvents()
{
	//reset down and released
	keysPressed = {};
	keysReleased = {};
	mouseButtonsPressed = {};
	mouseButtonsReleased = {};
	mousePos = (sf::Vector2f)sf::Mouse::getPosition(*window);
	typedText = "";
	scroll = sf::Vector2f(0.f, 0.f);
	while (window->pollEvent(event))
	{
		if (event.type == event.MouseWheelScrolled)
		{
			scroll.y = event.mouseWheelScroll.delta;
		}
		if (event.type == event.TextEntered)
		{
			typedText = event.text.unicode;
		}
		if (event.type == event.Closed)
		{
			if (game != nullptr)
			{
				SaveHandler::SaveGame();
			}
			window->close();
			exit(0);
		}
		if (event.type == event.KeyPressed)
		{
			auto code = event.key.code;
			if (getIndex(keysDown, code) == -1)
			{
				keysDown.push_back(code);
			}
			keysPressed.push_back(code);
		}
		if (event.type == event.KeyReleased)
		{
			auto code = event.key.code;
			int index = getIndex(keysDown, code);
			if (index != -1)
			{
				keysDown.erase(keysDown.begin() + index);
			}
			keysReleased.push_back(code);
		}
		if (event.type == event.MouseButtonPressed)
		{
			auto code = event.mouseButton.button;
			if (getIndex(mouseButtonsDown, code) == -1)
			{
				mouseButtonsDown.push_back(code);
			}
			mouseButtonsPressed.push_back(code);
		}
		if (event.type == event.MouseButtonReleased)
		{
			auto code = event.mouseButton.button;
			int index = getIndex(mouseButtonsDown, code);
			if (index != -1)
			{
				mouseButtonsDown.erase(mouseButtonsDown.begin() + index);
			}
			mouseButtonsReleased.push_back(code);
		}
	}
	if (keyPressed(sf::Keyboard::Key::F11))
	{
		isFullScreen = !isFullScreen;
		window->close();
		if (isFullScreen)
		{
			lastSmallWidth = width;
			lastSmallHeight = height;
			// Use the screenScalingFactor
			window->create(sf::VideoMode(width, height), "Cosmic Construction", sf::Style::Fullscreen);
			window->setFramerateLimit(200);
			sf::Image icon;
			icon.loadFromFile("resources/images/icon.png");
			window->setIcon(256, 256, icon.getPixelsPtr());
		}
		else
		{
			window->create(sf::VideoMode(lastSmallWidth, lastSmallHeight), "Cosmic Construction", sf::Style::Default);
			window->setFramerateLimit(200);
			sf::Image icon;
			icon.loadFromFile("resources/images/icon.png");
			window->setIcon(256, 256, icon.getPixelsPtr());
		}
	}
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
void InputHandler::RemoveKeyPressed(sf::Keyboard::Key key)
{
	int i = getIndex(keysPressed, key);
	if (i == -1)
	{
		return;
	}
	keysPressed.erase(keysPressed.begin() + i);
}
void InputHandler::RemoveKeyDown(sf::Keyboard::Key key)
{
	int i = getIndex(keysDown, key);
	if (i == -1)
	{
		return;
	}
	keysDown.erase(keysDown.begin() + getIndex(keysDown, key));
}
void InputHandler::RemoveKeyReleased(sf::Keyboard::Key key)
{
	int i = getIndex(keysReleased, key);
	if (i == -1)
	{
		return;
	}
	keysReleased.erase(keysReleased.begin() + getIndex(keysReleased, key));
}
void InputHandler::RemoveMouseButtonDown(sf::Mouse::Button button)
{
	int i = getIndex(mouseButtonsDown, button);
	if (i == -1)
	{
		return;
	}
	mouseButtonsDown.erase(mouseButtonsDown.begin() + getIndex(mouseButtonsDown, button));
}
void InputHandler::RemoveMouseButtonReleased(sf::Mouse::Button button)
{
	int i = getIndex(mouseButtonsReleased, button);
	if (i == -1)
	{
		return;
	}
	mouseButtonsReleased.erase(mouseButtonsReleased.begin() + getIndex(mouseButtonsReleased, button));
}
void InputHandler::RemoveMouseButtonPressed(sf::Mouse::Button button)
{
	int i = getIndex(mouseButtonsPressed, button);
	if (i == -1)
	{
		return;
	}
	mouseButtonsPressed.erase(mouseButtonsPressed.begin() + getIndex(mouseButtonsPressed, button));
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

std::vector<sf::Keyboard::Key> InputHandler::getAllKeysPressed()
{
	return keysPressed;
}