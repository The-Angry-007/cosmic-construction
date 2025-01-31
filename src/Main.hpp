#pragma once
#include "game.hpp"
#include "game/Tutorial.hpp"
#include "gui.hpp"
extern std::unique_ptr<sf::RenderWindow> window;
extern int width, height;
extern GUIHandler guihandler;
extern Game* game;
extern sf::Clock updateClock;
extern int numUpdates;
extern int currentBuild;
extern Tutorial* tutorial;