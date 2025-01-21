#include "RecipeHandler.hpp"
#include "Main.hpp"
#include "ResourceHandler.hpp"
#include "binds.hpp"
namespace RecipeHandler
{
std::vector<std::vector<RecipeData>> recipes;
GUI* gui = nullptr;
int guiStructure = -1;
int numBgObjs = 0;
}

void RecipeHandler::LoadRecipes(std::vector<JSON> jsons)
{
	recipes = {};
	for (int i = 0; i < ResourceHandler::numStructures; i++)
	{
		recipes.push_back({});
	}
	for (int i = 0; i < jsons.size(); i++)
	{
		JSON& j = jsons[i];
		RecipeData r;
		r.inputTypes = j.GetIntArr("inputTypes");
		r.inputAmounts = j.GetIntArr("inputAmounts");
		r.isFuels = j.GetBoolArr("isFuels");
		r.fuelLengths = j.GetFloatArr("fuelLengths");
		r.outputTypes = j.GetIntArr("outputTypes");
		r.outputAmounts = j.GetIntArr("outputAmounts");
		r.craftTime = j.GetFloat("craftTime");
		std::vector<int> structures = j.GetIntArr("StructureIDs");
		for (int j = 0; j < structures.size(); j++)
		{
			recipes[structures[j]].push_back(r);
		}
	}
}
void RecipeHandler::InitGUI(int structure)
{
	guiStructure = structure;
	gui = new GUI();
	GUIPanel* p = new GUIPanel(sf::Vector2f(0.5f, 0.5f), sf::Vector2f(0.4f, 0.4f), sf::Color(150, 150, 150));
	gui->AddObject(p);
	GUIPanel* topPanel = new GUIPanel(sf::Vector2f(0.5f, 0.13f), sf::Vector2f(0.4f, 0.03f), sf::Color(125, 125, 125));
	gui->AddObject(topPanel);
	Structure* s = game->ActivePlanet()->structures[structure];
	std::string name = "Select Recipe: " + ResourceHandler::structureTable->GetValue("Name", s->typeID);
	GUILabel* topLabel = new GUILabel(sf::Vector2f(0.5f, 0.13f), sf::Vector2f(0.9f, 0.025f), name);
	topLabel->SetColor(sf::Color::Black);
	gui->AddObject(topLabel);
	numBgObjs = gui->GUIObjects.size();
	if (s->recipe == nullptr)
	{
		//display menu to pick recipe
		std::vector<RecipeData> recs = recipes[s->typeID];
		float size = 0.05f;
		for (int i = 0; i < recs.size(); i++)
		{
			GUIItem* inpItem = new GUIItem(sf::Vector2f(0.f, 0.f), sf::Vector2f(size, size), recs[i].inputTypes[0], 0);
			GUIItem* outItem = new GUIItem(sf::Vector2f(0.f, 0.f), sf::Vector2f(size, size), recs[i].outputTypes[0], 0);
			inpItem->blocksMouseInput = true;
			outItem->blocksMouseInput = true;
			gui->AddObject(inpItem);
			gui->AddObject(outItem);
		}
	}
	else
	{
		//display menu of recipe
	}
	game->inMenu = true;
	guihandler.guis.push_back(gui);
}
void RecipeHandler::Update(float dt)
{
	if (gui != nullptr)
	{
		gui->Update(dt);
		Structure* s = game->ActivePlanet()->structures[guiStructure];
		float inoutgap = 0.015f;
		sf::Vector2f gap(0.1f + inoutgap, 0.1f);
		float size = 0.05f;
		sf::Vector2f spos(0.1f + size, 0.16f + size);
		// spos += gap;
		sf::Vector2f pos = spos;
		for (int i = numBgObjs; i < gui->GUIObjects.size(); i += 2)
		{
			//arranging items
			gui->GUIObjects[i]->position = pos;
			gui->GUIObjects[i + 1]->position = pos + sf::Vector2f(inoutgap, 0.f);
			if (gui->GUIObjects[i]->isClicked() || gui->GUIObjects[i + 1]->isClicked())
			{
				InputHandler::RemoveMbPressed(sf::Mouse::Button::Left);
				InputHandler::RemoveMbDown(sf::Mouse::Button::Left);
				s->SetRecipe(&recipes[s->typeID][(i - numBgObjs) / 2]);
				guihandler.guis.pop_back();
				delete gui;
				gui = nullptr;
				game->inMenu = false;
				break;
			}
			pos.x += gap.x;
			if (pos.x > 1 - spos.x)
			{
				pos.x = spos.x;
				pos.y += gap.y;
			}
		}
		if (InputHandler::pressed(binds::CloseInventory))
		{
			guihandler.guis.pop_back();
			delete gui;
			gui = nullptr;
			game->inMenu = false;
		}
	}
}
