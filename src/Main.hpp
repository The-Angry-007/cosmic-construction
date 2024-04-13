#pragma once
#include "Camera.hpp"
#include "Game.hpp"
#include "Gui/Gui.hpp"
#include "inputHandler.hpp"
extern sf::RenderWindow* window;
//the constant that determines the strength of gravity
extern InputHandler inp;
//extern Gui gui;
extern int width, height;
extern sf::Font* defaultFont;
extern Menu menu;
extern Game* game;
extern Camera camera;