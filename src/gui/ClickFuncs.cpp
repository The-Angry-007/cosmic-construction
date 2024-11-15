#include "ClickFuncs.hpp"
#include "Main.hpp"

void ClickFuncs::blankFunc()
{
	std::cout << "button was clicked" << std::endl;
}

void ClickFuncs::NextGUI()
{
	handler.OpenGUI(1);
}