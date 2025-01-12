#pragma once
#include "GUI.hpp"
#include "GUIButton.hpp"
#include "GUILabel.hpp"
#include "GUIPanel.hpp"
class BuildMenu : public GUI
{
public:
	std::vector<GUIButton*> tabs;
	int currentTab;
	GUIPanel* bg;
	GUILabel* infoText;
	GUILabel* infoLabel;
	GUILabel* costText;
	GUILabel* costLabel;
	GUIPanel* infoBG;
	std::vector<std::vector<GUIObject*>> menus;
	std::vector<std::vector<int>> typeIDs;
	BuildMenu();
	void Update(float dt);
	void Render();
	void SetTab(int tab);
};