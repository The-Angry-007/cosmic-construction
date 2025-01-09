#pragma once
#include "GUI.hpp"
#include "GUIButton.hpp"
#include "GUILabel.hpp"
#include "GUIPanel.hpp"
class BuildMenu : public GUI
{
public:
	std::vector<GUIButton*> tabs;
	GUIPanel* bg;
	GUILabel* infoLabel;
	BuildMenu();
	void Update(float dt);
	void Render();
};