#include "GUIHandler.hpp"

GUIHandler::GUIHandler()
{
	activeGui = 0;
	openedGuis = { 0 };
}

GUIHandler::~GUIHandler()
{
}

void GUIHandler::OpenGUI(int GUI)
{
	activeGui = GUI;
	openedGuis.push_back(GUI);
}
void GUIHandler::GoBack()
{
	if (openedGuis.size() > 1)
	{
		openedGuis.erase(openedGuis.end() - 1);
		activeGui = openedGuis[openedGuis.size() - 1];
	}
}

void GUIHandler::AddGUI(GUI gui)
{
	guis.push_back(gui);
}
void GUIHandler::Update(float dt)
{
	guis[activeGui].Update(dt);
}

void GUIHandler::Render()
{
	guis[activeGui].Render();
}