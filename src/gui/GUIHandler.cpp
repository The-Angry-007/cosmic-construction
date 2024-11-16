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
	GUIPanel* dimpanel = new GUIPanel(sf::Vector2f(0.5f, 0.5f), sf::Vector2f(0.5f, 0.5f), sf::Color(0, 0, 0, 100));

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
		GUIPanel* namePanel = new GUIPanel(sf::Vector2f(0.5f, 0.23f), sf::Vector2f(0.3f, 0.06f), sf::Color(191, 191, 191));
		GUIInputField* nameField = new GUIInputField(sf::Vector2f(0.5f, 0.23f), sf::Vector2f(0.25f, 0.05f));
		nameField->value = "Enter Save Name";
		g->AddObject(namePanel);
		g->AddObject(nameField);
		//the resources checkboxes
		GUILabel* resourcesLabel = new GUILabel(sf::Vector2f(0.5f, 0.333f), sf::Vector2f(0.278 / 2.f, 0.025f), "Resource Abundancy");
		g->AddObject(resourcesLabel);
		float p1 = 0.25f;
		float p4 = 0.9f;

		float p2 = Lerp(p1, p4, 0.333333f);
		float p3 = Lerp(p1, p4, 0.666667f);
		GUICheckbox* c1 = new GUICheckbox(sf::Vector2f(p1, 0.4f), sf::Vector2f(0.02032f, 0.2032f), sf::Color(166, 166, 166));
		c1->checked = true;
		GUICheckbox* c2 = new GUICheckbox(sf::Vector2f(p2, 0.4f), sf::Vector2f(0.02032f, 0.2032f), sf::Color(166, 166, 166));
		GUICheckbox* c3 = new GUICheckbox(sf::Vector2f(p3, 0.4f), sf::Vector2f(0.02032f, 0.2032f), sf::Color(166, 166, 166));
		c1->exclusives = { c2, c3 };
		c2->exclusives = { c1, c3 };
		c3->exclusives = { c1, c2 };

		GUILabel* l1 = new GUILabel(sf::Vector2f((p1 + p2) / 2.f, 0.4f), sf::Vector2f((p2 - p1 - 2 * 0.0232f) / 2.f - 0.01f, 0.0232f), "Sparce");
		l1->origin = sf::Vector2f(0.f, 0.5f);
		GUILabel* l2 = new GUILabel(sf::Vector2f((p2 + p3) / 2.f, 0.4f), sf::Vector2f((p3 - p2 - 2 * 0.0232f) / 2.f - 0.01f, 0.0232f), "Fair");
		l2->origin = sf::Vector2f(0.f, 0.5f);
		GUILabel* l3 = new GUILabel(sf::Vector2f((p3 + p4) / 2.f, 0.4f), sf::Vector2f((p4 - p3 - 2 * 0.0232f) / 2.f - 0.01f, 0.0232f), "Plenty");
		l3->origin = sf::Vector2f(0.f, 0.5f);
		g->AddObject(c1);
		g->AddObject(c2);
		g->AddObject(c3);
		g->AddObject(l1);
		g->AddObject(l2);
		g->AddObject(l3);
		//enter seed input field
		GUIPanel* seedPanel = new GUIPanel(sf::Vector2f(0.5f, 0.6f), sf::Vector2f(0.25f, 0.06f), sf::Color(191, 191, 191));
		GUIInputField* seedField = new GUIInputField(sf::Vector2f(0.5f, 0.6f), sf::Vector2f(0.2f, 0.04f));
		seedField->value = "Enter Seed";
		g->AddObject(seedPanel);
		g->AddObject(seedField);
		//create save button
		GUIImage* i = new GUIImage(sf::Vector2f(0.5f, 0.8f), sf::Vector2f(0.3f, 0.05f), "resources/images/buttonBezels.png");
		GUILabel* l = new GUILabel(sf::Vector2f(0.5f, 0.8f), sf::Vector2f(0.25f, 0.025f), "Create Save");
		l->SetColor(sf::Color::Black);
		GUIButton* b = new GUIButton(sf::Vector2f(0.5f, 0.8f), sf::Vector2f(0.3f, 0.05f), i, l);
		b->clickFunc = ClickFuncs::CreateSave;
		g->AddObject(b);
		guis.push_back(g);
	}
	//LOAD GAME MENU
	{
		GUI* g = new GUI();
		g->AddObject(galaxy);
		g->AddObject(dimpanel);
		//label at the top of the screen that says "load game"
		GUILabel* newgamelabel = new GUILabel(sf::Vector2f(0.5f, 0.05f), sf::Vector2f(0.5f, 0.03f), "Load Game");

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
	//MAIN GAME GUI
	{
		GUI* g = new GUI();
		GUILabel* l = new GUILabel(sf::Vector2f(0.5f, 0.5f), sf::Vector2f(0.3f, 0.1f), "main game gui");
		g->AddObject(l);
		GUIPanel* p = new GUIPanel(sf::Vector2f(0.5f, 0.8f), sf::Vector2f(0.2f, 0.1f), sf::Color(100, 100, 100));
		GUILabel* l2 = new GUILabel(sf::Vector2f(0.5f, 0.8f), sf::Vector2f(0.2f, 0.1f), "go back");
		GUIButton* b = new GUIButton(sf::Vector2f(0.5f, 0.8f), sf::Vector2f(0.2f, 0.1f), p, l2);
		b->clickFunc = backfunc;
		g->AddObject(b);
		guis.push_back(g);
	}
}