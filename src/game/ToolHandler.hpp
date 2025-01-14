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
	Structure* previewStructure;
	GUILabel* insufficientLabel;
	sf::Clock insufficientTimer;
	std::vector<GUIImage*> selectedImages;
	void ShowInsufficient();
	void Update(float dt, Planet* p);
	Structure* CreateStructure(int type);
	ToolHandler();
	~ToolHandler();
};