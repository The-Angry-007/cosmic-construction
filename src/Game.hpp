#pragma once
#include "Include.hpp"
class Item;
class Game
{
public:
	std::string savePath;
	bool paused;
	float gravity;
	void Update(double dt);
	void Render();
	void Init(bool newGame);
	void TogglePaused();
	void NewGame();
	bool mouseDragsItems;
	sf::Clock* timePassed;
	std::vector<Item> items;

	sf::VertexArray ItemVertices;
	Game();
	~Game();
};
