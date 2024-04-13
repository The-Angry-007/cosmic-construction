#include "Gui/ClickFuncs.hpp"
#include "Gui/Gui.hpp"
#include "Gui/SaveSlot.hpp"
#include "Main.hpp"
#include "SaveHandler.hpp"
Menu::Menu()
{
	openMenu = 0;
}
void Menu::AddGui(Gui gui)
{
	guis.push_back(gui);
}
void Menu::OpenMenu(int menu)
{
	if (menu == 3)
	{
		slots = {};
		std::vector<std::string> dirs = SaveHandler::listDirs(SaveHandler::workingDir);
		//this is all to sort by made newest first, it gets the time after 1970 it was created
		//for each file and uses that to put them in order (biggest first)
		std::vector<int> dates;
		for (uint i = 0; i < dirs.size(); i++)
		{
			int time = std::stoi(SaveHandler::getLines(SaveHandler::workingDir + "\\" + dirs[i] + "\\metadata.txt")[1]);
			dates.push_back(time);
		}
		//bubble sort algorithm (im lazy)
		for (uint i = 0; i < dates.size(); i++)
		{
			for (uint j = 0; j < dates.size() - i - 1; j++)
			{
				if (dates[j] < dates[j + 1])
				{
					int temp = dates[j];
					dates[j] = dates[j + 1];
					dates[j + 1] = temp;
					std::string temp2 = dirs[j];
					dirs[j] = dirs[j + 1];
					dirs[j + 1] = temp2;
				}
			}
		}
		for (uint i = 0; i < dirs.size(); i++)
		{
			slots.push_back(SaveSlot(dirs[i], sf::Vector2f(0.5f, 0.1f + 0.15f * i), sf::Vector2f(0.5f, 0.1f)));
		}
	}
	else
	{
		slots = {};
	}
	openMenu = menu;
	openedGuis.push_back(menu);
}
void Menu::Render(float dt)
{
	if (openMenu != -1 && guis.size() > (uint)openMenu)
	{
		guis[openMenu].Render(dt);
	}
	for (uint i = 0; i < slots.size(); i++)
	{
		slots[i].Render();
	}
}
void Menu::Update()
{
	if (openMenu != -1 && guis.size() > (uint)openMenu)
	{
		guis[openMenu].Update();
	}
	if (slots.size() != 0)
	{
		sf::Vector2f move = inp.scroll * 0.01f;

		for (uint i = 0; i < slots.size(); i++)
		{
			slots[i].Move(move);

			slots[i].Update();
		}
	}
}
void Menu::GoBack()
{
	if (openMenu == 2 || openMenu == 3)
	{
		SaveHandler::ResetDir();
	}
	openedGuis.pop_back();
	OpenMenu(openedGuis[openedGuis.size() - 1]);
	openedGuis.pop_back();
}
Menu InitMenu()
{
	Menu m;
	Gui mainMenu;
	mainMenu.Init();
	mainMenu.AddLabel(Label("Planet Sim", sf::Vector2f(0.5f, 0.2f), sf::Vector2f(0.7f, 0.2f), sf::Color::Black));
	sf::Texture moon;
	if (!moon.loadFromFile("resources/images/moon.png"))
	{
		std::cout << "did not open correctly" << std::endl;
	}

	mainMenu.AddPanel(Panel(sf::FloatRect(0.f, 0.f, 1.f, 1.f), sf::Color(100, 100, 100)));
	mainMenu.AddButton(Button(sf::Vector2f(0.5f, 1.f), sf::Vector2f(1.f, 2.f), sf::Color::Transparent, moon));
	mainMenu.AddButton(Button(sf::Vector2f(0.275f, 0.4f), sf::Vector2f(0.325f, 0.1f), sf::Color(50, 50, 50), "New Game", sf::Color::White, ClickFuncs::NewGame));
	mainMenu.AddButton(Button(sf::Vector2f(1 - 0.275f, 0.4f), sf::Vector2f(0.325f, 0.1f), sf::Color(50, 50, 50), "Load Game", sf::Color::White, ClickFuncs::LoadGame));
	mainMenu.AddButton(Button(sf::Vector2f(0.5f, 0.55f), sf::Vector2f(0.4f, 0.1f), sf::Color(50, 50, 50), "Options", sf::Color::White, ClickFuncs::Options));
	mainMenu.AddButton(Button(sf::Vector2f(0.5f, 0.7f), sf::Vector2f(0.4f, 0.1f), sf::Color(50, 50, 50), "Quit", sf::Color::White, ClickFuncs::Quit));
	m.AddGui(mainMenu);
	//options menu
	Gui options;
	options.Init();
	options.AddPanel(Panel(sf::FloatRect(0.f, 0.f, 1.f, 1.f), sf::Color(80, 80, 80)));
	options.AddButton(Button(sf::Vector2f(0.9f, 0.9f), sf::Vector2f(0.15f, 0.1f), sf::Color(50, 50, 50), "go back", sf::Color::White, ClickFuncs::GoBack));
	m.AddGui(options);
	//new game menu
	Gui newGame;
	newGame.Init();
	newGame.AddPanel(Panel(sf::FloatRect(0.f, 0.f, 1.f, 1.f), sf::Color(100, 100, 100)));
	newGame.AddButton(Button(sf::Vector2f(0.9f, 0.9f), sf::Vector2f(0.15f, 0.1f), sf::Color(50, 50, 50), "go back", sf::Color::White, ClickFuncs::GoBack));
	newGame.AddInpField(InputField(sf::Vector2f(0.5f, 0.4f), sf::Vector2f(0.3f, 0.1f), sf::Color(150, 150, 150), 20));
	newGame.AddLabel(Label("Enter a name", sf::Vector2f(0.5f, 0.3f), sf::Vector2f(0.3f, 0.1f), sf::Color::Black));
	newGame.AddButton(Button(sf::Vector2f(0.5f, 0.6f), sf::Vector2f(0.3f, 0.1f), sf::Color(80, 80, 80), "Create Save", sf::Color::Black, ClickFuncs::CreateSave));
	m.AddGui(newGame);
	Gui loadGame;
	loadGame.Init();
	loadGame.AddPanel(Panel(sf::FloatRect(0.f, 0.f, 1.f, 1.f), sf::Color(100, 100, 100)));
	loadGame.AddButton(Button(sf::Vector2f(0.9f, 0.9f), sf::Vector2f(0.15f, 0.1f), sf::Color(50, 50, 50), "go back", sf::Color::White, ClickFuncs::GoBack));
	m.AddGui(loadGame);
	Gui mainGame;
	mainGame.Init();
	Slider s(sf::Vector2f(0.9f, 0.9f), sf::Vector2f(0.03f, 0.3f));
	s.updateFunction = ClickFuncs::SetThrottle;
	mainGame.AddSlider(s);
	mainGame.AddLabel(Label("Throttle", sf::FloatRect(0.85f, 0.9f, 0.1f, 0.1f), sf::Color::White));
	m.AddGui(mainGame);
	Gui paused;
	paused.Init();
	paused.AddPanel(Panel(sf::FloatRect(0.f, 0.f, 1.f, 1.f), sf::Color(0, 0, 0, 100)));
	paused.AddLabel(Label("Paused", sf::Vector2f(0.5f, 0.2f), sf::Vector2f(0.8f, 0.1f), sf::Color::White));
	paused.AddButton(Button(sf::Vector2f(0.5f, 0.4f), sf::Vector2f(0.5f, 0.1f), sf::Color(100, 100, 100), "Resume Game", sf::Color::Black, ClickFuncs::ResumeGame));
	paused.AddButton(Button(sf::Vector2f(0.5f, 0.55f), sf::Vector2f(0.5f, 0.1f), sf::Color(100, 100, 100), "Options", sf::Color::Black, ClickFuncs::Options));
	paused.AddButton(Button(sf::Vector2f(0.5f, 0.7f), sf::Vector2f(0.5f, 0.1f), sf::Color(100, 100, 100), "Save and Quit", sf::Color::Black, ClickFuncs::QuitToTitle));
	m.AddGui(paused);
	m.OpenMenu(0);
	return m;
}
Gui* Menu::getOpenGui()
{
	return &guis[openMenu];
}