#include "Include.hpp"
void ClickFuncs::NewGame()
{
	menu.OpenMenu(2);
}
void ClickFuncs::LoadGame()
{
	menu.OpenMenu(3);
}
void ClickFuncs::Options()
{
	menu.OpenMenu(1);
}
void ClickFuncs::Quit()
{
	window->close();
}
void ClickFuncs::GoBack()
{
	menu.GoBack();
}
void ClickFuncs::CreateSave()
{
	SaveHandler::CreateSave(menu.getOpenGui()->inpFields[0].text);
	menu.OpenMenu(4);
	game = new Game();
	game->Init(true);
}

void ClickFuncs::ResumeGame()
{
	game->TogglePaused();
}

void ClickFuncs::QuitToTitle()
{
	SaveHandler::SaveGame();

	SaveHandler::ResetDir();

	game = nullptr;
	menu.OpenMenu(0);
}
