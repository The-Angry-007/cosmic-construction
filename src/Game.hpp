#pragma once
#include "box2d/box2d.h"
#include "parts/FuelTank.hpp"
#include "parts/Structure.hpp"
#include "parts/Thruster.hpp"
class Game
{
public:
	std::string savePath;
	bool paused;
	void Update(double dt);
	void Render();
	void Init(bool newGame);
	void TogglePaused();
	void NewGame();
	float thrusterThrottle;
	float timeScale;
	bool frozen;
	b2World* world;
	b2Body* groundBody;
	std::vector<b2Body*> blocks;
	std::vector<Structure> structures;
	sf::Clock* timePassed;
	Game();
	~Game();
};
extern sf::RectangleShape box2dBodyToSFML(b2Body* body, const sf::Color& color);
