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
		//galaxy background
		GUIGalaxy* galaxy = new GUIGalaxy();
		g->AddObject(galaxy);
		//cosmic construction logo
		GUIImage* logo = new GUIImage(sf::Vector2f(0.5f, 0.27f), sf::Vector2f(0.5f, 0.27f), "resources/images/cosmic construction logo 3.png");
		logo->keepAspectRatio = true;
		g->AddObject(logo);
		//new game, load game, settings, help buttons
		float top = 0.27f * 2.f + 0.05f;
		float bottom = 0.95f;
		float height = 0.033f;
		float width = 0.16f;
		GUIPanel* p1 = new GUIPanel(sf::Vector2f(0.5f, top), sf::Vector2f(width, height), sf::Color(100, 100, 100));
		GUILabel* l1 = new GUILabel(sf::Vector2f(0.5f, top), sf::Vector2f(width, height), "New Game");
		GUIButton* b1 = new GUIButton(sf::Vector2f(0.5f, top), sf::Vector2f(width, height), p1, l1);
		g->AddObject(b1);
		guis.push_back(g);
	}
}