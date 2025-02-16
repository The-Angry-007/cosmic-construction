#pragma once
#include "GUI.hpp"
#include "GUILabel.hpp"
#include "Settings.hpp"
class GUIHandler
{
public:
	std::vector<GUI*> guis;
	int activeGui;
	std::vector<int> openedGuis;

	Settings* settings;
	GUILabel* fpsLabel;
	GUIPanel* itemNameBG;
	GUILabel* itemName;
	int fps;
	std::vector<sf::Vector2f> toolPoses;
	int numTools;
	int numGUIs;
	sf::Font guifont;

	GUIHandler();
	//note that guihandler has no destructor as it persists throughout the entire runtime of the program

	void OpenGUI(int GUI);
	void GoBack();
	void AddGUI(GUI* gui);
	void Update(float dt);
	void Render();
	//creates all the gui menus used throughout the game
	void InitGUIS();
	GUI* GetOpenGUI();
};