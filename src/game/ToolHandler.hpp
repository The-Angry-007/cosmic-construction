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
	std::vector<GUIPanel*> bgObjs;
	std::vector<int> draggingItems;
	Item* hoveringItem;
	sf::Vector2f mouseStartDraggingPos;
	sf::Vector2f itemStartDraggingPos;
	int placeDir;
	Structure* previewStructure;
	GUILabel* insufficientLabel;
	sf::Clock insufficientTimer;
	std::vector<GUIImage*> selectedImages;
	void ShowInsufficient();
	void Update(float dt, Planet* p);
	void Render();
	Structure* CreateStructure(int type);
	ToolHandler();
	~ToolHandler();
};