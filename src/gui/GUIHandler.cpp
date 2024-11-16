#include "../gui.hpp"
#include "utils.hpp"
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

//the guis are in the following order:
/*
0: main menu
1: new game menu
2: load game menu
3: settings menu
4: help menu
5: main game gui
6: pause menu
7: tech tree
*/
void GUIHandler::InitGUIS()
{
	activeGui = 0;
	openedGuis = { 0 };
	guis = {};
	std::function<void()> backfunc = std::bind(&GUIHandler::GoBack, this);

	//the galaxy background is outside the scope since multiple guis share it
	GUIGalaxy* galaxy = new GUIGalaxy();
	//same thing with the panel to dim the background
	GUIPanel* dimpanel = new GUIPanel(sf::Vector2f(0.5f, 0.5f), sf::Vector2f(0.5f, 0.5f), sf::Color(0, 0, 0, 75));

	//some weird C++ syntax - using {} creates a new local scope
	//this is done to have multiple variables under the same name within this function (since each is temporary)
	//MAIN MENU
	{
		GUI* g = new GUI();
		//galaxy background
		g->AddObject(galaxy);
		g->AddObject(dimpanel);
		//cosmic construction logo
		GUIImage* logo = new GUIImage(sf::Vector2f(0.5f, 0.3f), sf::Vector2f(0.5f, 0.3f), "resources/images/cosmic construction logo 3.png");
		logo->keepAspectRatio = true;
		g->AddObject(logo);
		//new game, load game, settings, help buttons
		float top = 0.27f * 2.f + 0.05f;
		float bottom = 0.9f;
		float height = 0.033f;
		float width = 0.16f;
		std::string labels[4] = { "New Game", "Load Game", "Settings", "Help" };
		std::function<void()> funcs[4] = { ClickFuncs::OpenNewGame, ClickFuncs::OpenLoadGame, ClickFuncs::OpenSettings, ClickFuncs::OpenHelp };
		for (int i = 0; i < 4; i++)
		{
			float y = Lerp(top, bottom, i / 3.f);
			// GUIPanel* p1 = new GUIPanel(sf::Vector2f(0.5f, y), sf::Vector2f(width, height), sf::Color(100, 100, 100));
			GUIImage* p1 = new GUIImage(sf::Vector2f(0.5f, y), sf::Vector2f(width, height), "resources/images/buttonBezels.png");
			GUILabel* l1 = new GUILabel(sf::Vector2f(0.5f, y), sf::Vector2f(width - 0.01f, height - 0.01f), labels[i]);
			l1->SetColor(sf::Color::Black);
			GUIButton* b1 = new GUIButton(sf::Vector2f(0.5f, y), sf::Vector2f(width, height), p1, l1);
			b1->clickFunc = funcs[i];
			g->AddObject(b1);
		}

		guis.push_back(g);
	}
	//NEW GAME MENU
	{
		GUI* g = new GUI();
		g->AddObject(galaxy);
		g->AddObject(dimpanel);
		//label at the top of the screen that says "new game"
		GUILabel* newgamelabel = new GUILabel(sf::Vector2f(0.5f, 0.05f), sf::Vector2f(0.5f, 0.03f), "New Game");
		g->AddObject(newgamelabel);
		//enter save name input field
		GUIPanel* namePanel = new GUIPanel(sf::Vector2f(0.5f, 0.23f), sf::Vector2f(0.3f, 0.06f), sf::Color(150, 150, 150));
		GUIInputField* nameField = new GUIInputField(sf::Vector2f(0.5f, 0.23f), sf::Vector2f(0.25f, 0.055f));
		nameField->value = "Enter Save Name";
		g->AddObject(namePanel);
		g->AddObject(nameField);
		guis.push_back(g);
	}
	//LOAD GAME MENU
	{
		GUI* g = new GUI();
		GUILabel* l = new GUILabel(sf::Vector2f(0.5f, 0.5f), sf::Vector2f(0.3f, 0.1f), "load game menu");
		g->AddObject(l);
		GUIPanel* p = new GUIPanel(sf::Vector2f(0.5f, 0.8f), sf::Vector2f(0.2f, 0.1f), sf::Color(100, 100, 100));
		GUILabel* l2 = new GUILabel(sf::Vector2f(0.5f, 0.8f), sf::Vector2f(0.2f, 0.1f), "go back");
		GUIButton* b = new GUIButton(sf::Vector2f(0.5f, 0.8f), sf::Vector2f(0.2f, 0.1f), p, l2);
		b->clickFunc = backfunc;
		g->AddObject(b);
		guis.push_back(g);
	}
	//SETTINGS MENU
	{
		GUI* g = new GUI();
		GUILabel* l = new GUILabel(sf::Vector2f(0.5f, 0.5f), sf::Vector2f(0.3f, 0.1f), "settings menu");
		g->AddObject(l);
		GUIPanel* p = new GUIPanel(sf::Vector2f(0.5f, 0.8f), sf::Vector2f(0.2f, 0.1f), sf::Color(100, 100, 100));
		GUILabel* l2 = new GUILabel(sf::Vector2f(0.5f, 0.8f), sf::Vector2f(0.2f, 0.1f), "go back");
		GUIButton* b = new GUIButton(sf::Vector2f(0.5f, 0.8f), sf::Vector2f(0.2f, 0.1f), p, l2);
		b->clickFunc = backfunc;
		g->AddObject(b);
		guis.push_back(g);
	}
	//HELP MENU
	{
		GUI* g = new GUI();
		GUILabel* l = new GUILabel(sf::Vector2f(0.5f, 0.5f), sf::Vector2f(0.3f, 0.1f), "help menu");
		g->AddObject(l);
		GUIPanel* p = new GUIPanel(sf::Vector2f(0.5f, 0.8f), sf::Vector2f(0.2f, 0.1f), sf::Color(100, 100, 100));
		GUILabel* l2 = new GUILabel(sf::Vector2f(0.5f, 0.8f), sf::Vector2f(0.2f, 0.1f), "go back");
		GUIButton* b = new GUIButton(sf::Vector2f(0.5f, 0.8f), sf::Vector2f(0.2f, 0.1f), p, l2);
		b->clickFunc = backfunc;
		g->AddObject(b);
		guis.push_back(g);
	}
}