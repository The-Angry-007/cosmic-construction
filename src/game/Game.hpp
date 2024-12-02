#pragma once
#include "Camera.hpp"
#include "Item.hpp"
class Game
{
public:
	bool paused;
	Item* item;
	Camera* camera;
	Game();
	~Game();
	void TogglePaused();
	void NewGame();
	void LoadGame();
	void Update(float dt);
	void Render();
};