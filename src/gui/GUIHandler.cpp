#include "GUIHandler.hpp"

GUIHandler::GUIHandler()
{
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
	if (openedGuis.size() > 0)
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