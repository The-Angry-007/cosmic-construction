#pragma once
class InputHandler
{
public:
	void ProcessEvents();
	bool keyDown(sf::Keyboard::Key key);
	bool keyPressed(sf::Keyboard::Key key);
	bool keyReleased(sf::Keyboard::Key key);
	bool mbDown(sf::Mouse::Button button);
	bool mbPressed(sf::Mouse::Button button);
	bool mbReleased(sf::Mouse::Button button);
	void RemoveKeyPressed(sf::Keyboard::Key key);
	void RemoveKeyDown(sf::Keyboard::Key key);
	void RemoveKeyReleased(sf::Keyboard::Key key);
	void RemoveMouseButtonPressed(sf::Mouse::Button button);
	void RemoveMouseButtonDown(sf::Mouse::Button button);
	void RemoveMouseButtonReleased(sf::Mouse::Button button);
	sf::Vector2f mousePos;
	sf::Vector2f screenToWorldPos(sf::Vector2f pos);
	InputHandler();
	std::vector<sf::Keyboard::Key> getAllKeysPressed();
	std::string typedText;
	sf::Vector2f scroll;
	bool isFullScreen;
	int lastSmallWidth;
	int lastSmallHeight;

private:
	sf::Event event;
	std::vector<sf::Keyboard::Key> keysDown;
	std::vector<sf::Keyboard::Key> keysPressed;
	std::vector<sf::Keyboard::Key> keysReleased;
	std::vector<sf::Mouse::Button> mouseButtonsDown;
	std::vector<sf::Mouse::Button> mouseButtonsPressed;
	std::vector<sf::Mouse::Button> mouseButtonsReleased;
	int getIndex(std::vector<sf::Keyboard::Key> keys, sf::Keyboard::Key key);
	int getIndex(std::vector<sf::Mouse::Button> buttons, sf::Mouse::Button button);
};