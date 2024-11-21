#include "ClickFuncs.hpp"
#include "../saving.hpp"
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

void ClickFuncs::CreateSave()
{
	GUI* gui = guihandler.GetOpenGUI();
	auto objects = gui->GUIObjects;
	int difficulty = 0;

	for (uint i = 0; i < 3; i++)
	{
		GUICheckbox* c = dynamic_cast<GUICheckbox*>(objects[objects.size() - 1 - i]);
		if (c->checked)
		{
			difficulty = i;
		}
	}
	std::string seed = dynamic_cast<GUIInputField*>(objects[objects.size() - 4])->value;
	std::string name = dynamic_cast<GUIInputField*>(objects[objects.size() - 5])->value;
	if (name == "Enter Save Name")
	{
		name = "Unnamed";
	}
	if (seed == "Enter Seed")
	{
		seed = std::to_string(rand() % 10000);
	}
	SaveHandler::CreateSave(name, difficulty, seed);
	guihandler.OpenGUI(5);
}