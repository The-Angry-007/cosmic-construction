#include "ClickFuncs.hpp"
#include "Main.hpp"

void ClickFuncs::blankFunc(GUIButton* button)
{
	std::cout << "button was clicked" << std::endl;
}

void ClickFuncs::NextGUI(GUIButton* button)
{
	handler.activeGui++;
}