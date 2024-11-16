#include "../gui.hpp"

GUIHandler::GUIHandler()
{
	activeGui = 0;
	openedGuis = { 0 };
	guis = {};
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

void GUIHandler::AddGUI(GUI* gui)
{
	guis.push_back(gui);
}
void GUIHandler::Update(float dt)
{
	guis[activeGui]->Update(dt);
}

void GUIHandler::Render()
{
	guis[activeGui]->Render();
}

GUI* GUIHandler::GetOpenGUI()
{
	return guis[activeGui];
}

void GUIHandler::InitGUIS()
{
	activeGui = 0;
	openedGuis = { 0 };
	guis = {};
	//some weird C++ syntax - using {} creates a new local scope
	//this is done to have multiple variables under the same name within this function (since each is temporary)
	//MAIN MENU
	{
		GUI* g = new GUI();
		GUIGalaxy* galaxy = new GUIGalaxy();
		g->AddObject(galaxy);
		guis.push_back(g);
	}
}