#pragma once
#include "Camera.hpp"
#include "Item.hpp"
#include "saving.hpp"
class Planet
{
public:
	//0-7 for each planet in the solar system
	int id;
	std::vector<Item> items;
	Camera camera;
	sf::Color backgroundColor;
	int draggingItem;
	sf::Vector2f mouseStartDraggingPos;
	sf::Vector2f itemStartDraggingPos;
	Planet(int id);
	void Update(float dt);
	void Render();
};