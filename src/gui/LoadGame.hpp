#pragma once
#include "../gui.hpp"

class LoadGame : public GUI
{
public:
	std::vector<GUISaveSlot*> saveSlots;
	LoadGame(GUIGalaxy* galaxy, GUIPanel* dimpanel);
	void Update(float dt);
	void Render();
};