#include "ClickFuncs.hpp"
#include "Main.hpp"

void ClickFuncs::blankFunc()
{
	std::cout << "button was clicked" << std::endl;
}

void ClickFuncs::OpenNewGame()
{
	guihandler.OpenGUI(1);
}
void ClickFuncs::OpenLoadGame()
{
	guihandler.OpenGUI(2);
}
void ClickFuncs::OpenSettings()
{
	guihandler.OpenGUI(3);
}
void ClickFuncs::OpenHelp()
{
	guihandler.OpenGUI(4);
}