#include "ClickFuncs.hpp"
#include "../saving.hpp"
#include "Main.hpp"

//default click function that buttons use
void ClickFuncs::blankFunc()
{
}
//the functions that open the correct gui when menu buttons are clicked
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
	GUI* g = new GUI();
	g->AddObject(guihandler.guis[0]->GUIObjects[0]);
	g->AddObject(guihandler.guis[0]->GUIObjects[1]);
	guihandler.settings->behindGUI = g;
	guihandler.OpenGUI(3);
}
void ClickFuncs::OpenHelp()
{
	guihandler.OpenGUI(4);
}
//the function called when the create save button is clicked.
void ClickFuncs::CreateSave()
{
	GUI* gui = guihandler.GetOpenGUI();
	//get all the objects in the create save menu
	auto objects = gui->GUIObjects;
	//the difficulty (sparse, fair, plenty) is stored as integer that can be 0,1 or 2.
	int difficulty = 0;
	//finds what the difficulty should be by checking whether each checkbox is checked
	for (uint i = 0; i < 3; i++)
	{
		//converts a guiobject pointer to a checkbox pointer so that the checked attribute can be accessed
		GUICheckbox* c = dynamic_cast<GUICheckbox*>(objects[objects.size() - 1 - i]);
		if (c->checked)
		{
			difficulty = i;
		}
	}
	//read the value of the seed input field
	std::string seed = dynamic_cast<GUIInputField*>(objects[objects.size() - 4])->value;
	//read the value of the name input field
	std::string name = dynamic_cast<GUIInputField*>(objects[objects.size() - 5])->value;
	//if the name has not been changed, make it "Unnamed"
	if (name == "Enter Save Name")
	{
		name = "Unnamed";
	}
	//same with the seed, but it becomes a number between 0 and 9999
	if (seed == "Enter Seed")
	{
		seed = std::to_string(rand() % 10000);
	}
	//create the save with the name, difficulty and seed calculated
	SaveHandler::CreateSave(name, difficulty, seed);
	//switch to the main game gui
	guihandler.OpenGUI(5);
}

void ClickFuncs::ResumeGame()
{
	game->TogglePaused();
}
void ClickFuncs::OpenSettingsInGame()
{
	guihandler.settings->behindGUI = new GUI();
	guihandler.OpenGUI(3);
}
void ClickFuncs::SaveAndQuit()
{
	SaveHandler::SaveGame();
	// delete game;
	game = nullptr;
	SaveHandler::ResetWorkingDir();
	guihandler.OpenGUI(0);
}