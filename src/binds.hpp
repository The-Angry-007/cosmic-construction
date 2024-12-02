#pragma once

//a namespace that contains the codes for keybinds
namespace binds
{
extern int Pause;
extern int Fullscreen;
extern int Pan;
int keyToCode(sf::Keyboard::Key key);
int buttonToCode(sf::Mouse::Button button);
std::string GetName(int code);
}