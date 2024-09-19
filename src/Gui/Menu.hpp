#pragma once
class SaveSlot;
/*
this isnt so much of a menu class anymore, although thats what it started as.
its now more of a collection of guis that can be accessed at any time during runtime.
for example, the menu object created on startup was supposed to only be the main menu,
but it contained the options gui that needed to be used when accessed through the pause menu.
*/
class Gui;
class Menu
{
public:
	Menu();
	void OpenMenu(int menu);
	//re opens previous gui
	void GoBack();
	void AddGui(Gui gui);
	void Update(float dt);
	void Render(float dt);
	Gui* getOpenGui();
	std::vector<SaveSlot> slots;

private:
	int openMenu;
	std::vector<Gui> guis;
	std::vector<int> openedGuis;
};

extern Menu InitMenu();