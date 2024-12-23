#pragma once
#include "InputHandler.hpp"
#include "Planet.hpp"
#include "gui.hpp"
class ToolHandler
{
public:
	int selectedTool;
	int lastPlacedStructure;
	int placeType;
	sf::Vector2i prevTilePos;
	GUIObject* selectedObj;
	std::vector<GUIImage*> bgObjs;
	int hoveringItem;
	int draggingItem;
	sf::Vector2f mouseStartDraggingPos;
	sf::Vector2f itemStartDraggingPos;
	int placeDir;
	void Update(float dt, Planet* p);
	ToolHandler();
};