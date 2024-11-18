#pragma once
#include "GUI.hpp"
#include "Settings.hpp"
class GUIHandler
{
public:
	std::vector<GUI*> guis;
	int activeGui;
	std::vector<int> openedGuis;

	Settings* settings;

	GUIHandler();
	~GUIHandler();

	void OpenGUI(int GUI);
	void GoBack();
	void AddGUI(GUI* gui);
	void Update(float dt);
	void Render();
	//creates all the gui menus used throughout the game
	void InitGUIS();
	GUI* GetOpenGUI();
};