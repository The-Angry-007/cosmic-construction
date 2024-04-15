#pragma once
#include "box2d/box2d.h"
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
	sf::Clock* timePassed;
	Game();
	~Game();
};
