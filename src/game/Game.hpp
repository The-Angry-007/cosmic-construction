#pragma once
class Game
{
public:
	bool paused;

	Game();
	~Game();
	void TogglePaused();
	void NewGame();
	void LoadGame();
	void Update(float dt);
	void Render();
};