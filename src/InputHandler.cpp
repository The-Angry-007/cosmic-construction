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
