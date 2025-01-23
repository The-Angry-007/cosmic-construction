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
	sf::Vector2f structureStartDraggingPos;
	int draggingStructure;
	int placeDir;
	sf::Vector2f prevmousepos;
	Structure* previewStructure;
	GUILabel* insufficientLabel;
	sf::Clock insufficientTimer;
	std::vector<GUIObject*> tallyObjs;
	std::vector<GUIImage*> selectedImages;
	void ShowSelectArea(sf::Vector2i pos, int width, int height, sf::Color col);
	void ShowInsufficient();
	void ReloadTally(sf::Vector2i tilePos);
	void ClearTally();
	void Update(float dt, Planet* p);
	void Render();
	Structure* CreateStructure(int type);
	ToolHandler();
	~ToolHandler();
};