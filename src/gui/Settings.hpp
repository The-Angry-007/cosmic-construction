#pragma once
#include "GUI.hpp"

//a special class for the settings gui.
class Settings : public GUI
{
public:
	//whatever should be behind the settings interface
	GUI* behindGUI;
	//one persistent gui, then one that is overlaid on top
	GUI* bgGUI;
	std::vector<GUI*> pageGuis;
	int currentGUI;

	int framerate;
	int saveInterval;
	//this is for the controls

	Settings();
	~Settings();
	void Update(float dt);

	void Render();
	int selectedBind;
	std::vector<int*> bindCodes;
	std::vector<GUI*> bindGUIs;
	void AddBind(std::string label, int* value);
};