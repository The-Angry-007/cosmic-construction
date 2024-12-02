#pragma once
#include "Item.hpp"
class Game
{
public:
	bool paused;
	Item* item;
	Game();
	~Game();
	void TogglePaused();
	void NewGame();
	void LoadGame();
	void Update(float dt);
	void Render();
};