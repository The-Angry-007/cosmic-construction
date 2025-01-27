#include "../gui.hpp"
#include "../saving.hpp"
#include "BuildMenu.hpp"
#include "InputHandler.hpp"
#include "Main.hpp"
#include "binds.hpp"
#include "game/RecipeHandler.hpp"
#include "utils.hpp"
//constructor
GUIHandler::GUIHandler()
{
	activeGui = 0;
	openedGuis = { 0 };
	guis = {};
}

//sets the active gui to the gui given
void GUIHandler::OpenGUI(int GUI)
{
	// //if the gui to switch to is not the main game, reset the working directory
	// if (GUI != 5 && GUI != 6)
	// {
	// 	SaveHandler::ResetWorkingDir();
	// 	delete game;
	// 	game = nullptr;
	// }
	//set the active gui to the gui given and push the new index to the stack
	activeGui = GUI;
	openedGuis.push_back(GUI);
	//if it is 3, reset the current page of the settings gui
	if (GUI == 3)
	{
		dynamic_cast<Settings*>(guis[activeGui])->currentGUI = 0;
	}
	//otherwise, if it is 2, reload the save slots in the load game gui
	else if (GUI == 2)
	{
		dynamic_cast<LoadGame*>(guis[activeGui])->Reload();
	}
}
//if there is more than one opened gui in the stack, pop it and open the new top gui in the stack.
//note that the new gui must also be erased since it will be re-added when opened
void GUIHandler::GoBack()
{
	//exiting out of settings
	if (openedGuis[openedGuis.size() - 1] == 3)
	{
		settings->SaveSettings();
	}
	if (openedGuis.size() > 1)
	{
		openedGuis.erase(openedGuis.end() - 1);
		activeGui = openedGuis[openedGuis.size() - 1];
		openedGuis.erase(openedGuis.end() - 1);
		OpenGUI(activeGui);
	}
}
//simply pushes the new gui to the list of guis
void GUIHandler::AddGUI(GUI* gui)
{
	guis.push_back(gui);
}
//updates the active gui
void GUIHandler::Update(float dt)
{
	itemName = nullptr;
	itemNameBG = nullptr;
	if (guis.size() > numGUIs && activeGui == 5)
	{
		guis[guis.size() - 1]->Update(dt);
	}
	guis[activeGui]->Update(dt);
	//the pause keybind also serves as a back button in menus that arent the main game gui
	if (activeGui != 5 && InputHandler::pressed(binds::Pause) && activeGui != 6 && activeGui != 0 && activeGui != 7)
	{
		GoBack();
	}
	fps = (int)(1.f / dt);
	fpsLabel->value = std::to_string(fps) + " fps";
}
//render the active gui
void GUIHandler::Render()
{
	sf::View currentView = window->getView();
	sf::View GUIView(sf::FloatRect(0.f, 0.f, width, height));
	window->setView(GUIView);
	guis[activeGui]->Render();
	if (guis.size() > numGUIs && activeGui == 5)
	{
		guis[guis.size() - 1]->Render();
	}
	if (itemName != nullptr)
	{
		itemNameBG->Render();
		itemName->Render();
	}
	fpsLabel->Render();
	window->setView(currentView);
}
//return the active gui
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
7: build menu
*/
void GUIHandler::InitGUIS()
{
	guifont.loadFromFile("content/resources/fonts/default font.ttf");
	activeGui = 0;
	openedGuis = { 0 };
	guis = {};
	//get a reference to the go back function of this object
	std::function<void()> backfunc = std::bind(&GUIHandler::GoBack, this);

	//the galaxy background is outside the scope since multiple guis share it
	GUIGalaxy* galaxy = new GUIGalaxy();
	//same thing with the panel to dim the background
	GUIPanel* dimpanel = new GUIPanel(sf::Vector2f(0.5f, 0.5f), sf::Vector2f(0.5f, 0.5f), sf::Color(0, 0, 0, 100));

	fpsLabel = new GUILabel(sf::Vector2f(0.1f, 0.03f), sf::Vector2f(0.1f, 0.03f), "");
	fpsLabel->origin = sf::Vector2f(0.f, 0.f);

	//using {} creates a new local scope
	//this is done to have multiple variables under the same name within this function (since each is temporary)

	//the specifics of each of these menus is not very important, it is just definining the positions and sizes of various gui objects
	//MAIN MENU
	{
		GUI* g = new GUI();
		//galaxy background
		g->AddObject(galaxy);
		g->AddObject(dimpanel);
		//cosmic construction logo
		GUIImage* logo = new GUIImage(sf::Vector2f(0.5f, 0.3f), sf::Vector2f(0.5f, 0.3f), "content/resources/images/cosmic construction logo 3.png");
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
			GUIImage* p1 = new GUIImage(sf::Vector2f(0.5f, y), sf::Vector2f(width, height), "content/resources/images/buttonBezels.png");
			GUILabel* l1 = new GUILabel(sf::Vector2f(0.5f, y), sf::Vector2f(width - 0.01f, height - 0.01f), labels[i]);
			if (i == 0)
			{
				l1->altCharSize = true;
			}
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

		g->AddObject(l1);
		g->AddObject(l2);
		g->AddObject(l3);
		//enter seed input field
		GUIPanel* seedPanel = new GUIPanel(sf::Vector2f(0.5f, 0.6f), sf::Vector2f(0.25f, 0.06f), sf::Color(191, 191, 191));
		GUIInputField* seedField = new GUIInputField(sf::Vector2f(0.5f, 0.6f), sf::Vector2f(0.2f, 0.04f));
		seedField->value = "Enter Seed";
		g->AddObject(seedPanel);
		//create save button
		GUIImage* i = new GUIImage(sf::Vector2f(0.5f, 0.8f), sf::Vector2f(0.3f, 0.05f), "content/resources/images/buttonBezels.png");
		GUILabel* l = new GUILabel(sf::Vector2f(0.5f, 0.8f), sf::Vector2f(0.25f, 0.025f), "Create Save");
		l->SetColor(sf::Color::Black);
		GUIButton* b = new GUIButton(sf::Vector2f(0.5f, 0.8f), sf::Vector2f(0.3f, 0.05f), i, l);
		b->clickFunc = ClickFuncs::CreateSave;
		g->AddObject(b);
		g->AddObject(nameField);
		g->AddObject(seedField);
		g->AddObject(c1);
		g->AddObject(c2);
		g->AddObject(c3);
		guis.push_back(g);
	}
	//LOAD GAME MENU
	{
		LoadGame* l = new LoadGame(galaxy, dimpanel);
		guis.push_back(l);
	}
	//SETTINGS MENU
	{
		Settings* s = new Settings();
		GUI* bg = new GUI();
		bg->AddObject(galaxy);
		bg->AddObject(dimpanel);
		s->behindGUI = bg;
		guis.push_back(s);
		//used to get framerate, etc
		this->settings = s;
	}
	//the following two menus are incomplete, so they are just placeholders for now.
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
		// GUILabel* l = new GUILabel(sf::Vector2f(0.5f, 0.5f), sf::Vector2f(0.3f, 0.1f), "main game gui");
		// g->AddObject(l);
		// GUIPanel* p = new GUIPanel(sf::Vector2f(0.5f, 0.8f), sf::Vector2f(0.2f, 0.1f), sf::Color(100, 100, 100));
		// GUILabel* l2 = new GUILabel(sf::Vector2f(0.5f, 0.8f), sf::Vector2f(0.2f, 0.1f), "go back");
		// GUIButton* b = new GUIButton(sf::Vector2f(0.5f, 0.8f), sf::Vector2f(0.2f, 0.1f), p, l2);
		// b->clickFunc = backfunc;
		// g->AddObject(b);
		numTools = 3;
		std::string paths[3] = { "GUIHammer.png", "GUIGrab.png", "GUIDelete.png" };
		sf::Vector2f middle(0.5f, 0.85f);
		float size = 0.08f;
		for (int i = 0; i < numTools; i++)
		{
			sf::Vector2f totalSize((numTools - 1) * size, 0.f);
			sf::Vector2f left = middle - totalSize / 2.f;
			sf::Vector2f right = middle + totalSize / 2.f;
			sf::Vector2f pos = Lerp(left, right, i / (numTools - 1.f));
			GUIPanel* outline = new GUIPanel(pos, sf::Vector2f(size, size) / 2.f * 1.4f, sf::Color(150, 150, 150));
			outline->keepAspectRatio = true;
			outline->ratio = 1.f;
			g->AddObject(outline);
		}
		toolPoses = {};
		for (int i = 0; i < numTools; i++)
		{
			sf::Vector2f left = middle - sf::Vector2f(size * (numTools - 1), 0) / 2.f;
			sf::Vector2f right = middle + sf::Vector2f(size * (numTools - 1), 0) / 2.f;
			sf::Vector2f pos = Lerp(left, right, i / (numTools - 1.f));
			toolPoses.push_back(pos);
			std::string path = "content\\resources\\images\\" + paths[i];
			GUIPanel* bg = new GUIPanel(pos, sf::Vector2f(size, size) / 2.f * 1.2f, sf::Color(50, 50, 50));
			bg->keepAspectRatio = true;
			bg->ratio = 1.f;

			g->AddObject(bg);
			GUIImage* im = new GUIImage(pos, sf::Vector2f(size, size) / 2.f, path);
			im->keepAspectRatio = true;
			g->AddObject(im);
		}
		GUIImage* selectedTool = new GUIImage(toolPoses[0], sf::Vector2f(size, size) / 2.f / 16.f * 24.f, "content\\resources\\images\\GUISelectedTool.png");
		selectedTool->keepAspectRatio = true;
		g->AddObject(selectedTool);
		{
			float size = 0.05f;
			GUIImage* im = new GUIImage(sf::Vector2f(1.f - size, size), sf::Vector2f(size, size), "content\\resources\\images\\GUIHome.png");
			im->keepAspectRatio = true;
			im->origin = sf::Vector2f(1.f, 0.f);
			GUIButton* b = new GUIButton(sf::Vector2f(1.f - size, size), sf::Vector2f(size, size), im, nullptr);
			b->clickFunc = ClickFuncs::ResetCamPos;
			b->dimObj = nullptr;
			g->AddObject(b);
		}
		guis.push_back(g);
	}
	//PAUSE GUI
	{
		GUI* g = new GUI();
		GUIPanel* p = new GUIPanel(sf::Vector2f(0.5f, 0.5f), sf::Vector2f(0.5f, 0.5f), sf::Color(0, 0, 0, 100));
		g->AddObject(p);
		GUILabel* l = new GUILabel(sf::Vector2f(0.5f, 0.1f), sf::Vector2f(0.4f, 0.05f), "Game Paused");
		l->SetColor(sf::Color::White);
		g->AddObject(l);
		float top = 0.4f;
		float bottom = 0.74f;
		float height = 0.04f;
		float width = 0.25f;
		std::string labels[4] = { "Resume Game", "Help", "Settings", "Save And Quit" };
		std::function<void()> funcs[4] = { ClickFuncs::ResumeGame, ClickFuncs::OpenHelp, ClickFuncs::OpenSettingsInGame, ClickFuncs::SaveAndQuit };
		for (int i = 0; i < 4; i++)
		{
			float y = Lerp(top, bottom, i / 3.f);
			// GUIPanel* p1 = new GUIPanel(sf::Vector2f(0.5f, y), sf::Vector2f(width, height), sf::Color(100, 100, 100));
			GUIImage* p1 = new GUIImage(sf::Vector2f(0.5f, y), sf::Vector2f(width, height), "content/resources/images/buttonBezels.png");
			GUILabel* l1 = new GUILabel(sf::Vector2f(0.5f, y), sf::Vector2f(width - 0.01f, height - 0.01f), labels[i]);
			l1->SetColor(sf::Color::Black);
			GUIButton* b1 = new GUIButton(sf::Vector2f(0.5f, y), sf::Vector2f(width, height), p1, l1);
			b1->clickFunc = funcs[i];
			g->AddObject(b1);
		}
		guis.push_back(g);
	}
	BuildMenu* b = new BuildMenu();
	guis.push_back(b);
	numGUIs = guis.size();
}
