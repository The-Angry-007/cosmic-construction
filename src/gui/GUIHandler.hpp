#pragma once
#include "GUI.hpp"
class GUIHandler
{
public:
	std::vector<GUI> guis;
	int activeGui;
	std::vector<int> openedGuis;

	GUIHandler();
	~GUIHandler();
	void OpenGUI(int GUI);
	void GoBack();
	void AddGUI(GUI gui);
	void Update(float dt);
	void Render();
	GUI* GetOpenGUI();
};