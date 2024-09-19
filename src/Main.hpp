#pragma once
#include "Include.hpp"
class Timer;
class InputHandler;
extern sf::RenderWindow* window;
//the constant that determines the strength of gravity
extern InputHandler inp;
//extern Gui gui;
extern int width, height;
extern sf::Font* defaultFont;
extern sf::Font* pixelFont;
extern Menu menu;
extern Game* game;
extern Camera camera;
extern Timer timer;
