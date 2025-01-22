#include "RecipeHandler.hpp"
#include "Main.hpp"
#include "Recipe.hpp"
#include "ResourceHandler.hpp"
#include "binds.hpp"
#include "utils.hpp"
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
		numBgObjs++;
		GUIImage* arrow = new GUIImage(sf::Vector2f(0.5f, 0.5f), sf::Vector2f(0.25f, 0.3f), "resources\\images\\arrow.png");
		arrow->keepAspectRatio = true;
		gui->AddObject(arrow);
		//display menu of recipe
		float inputEnd = 0.25f;
		float outputStart = 0.75f;
		float size = 0.05f;
		float gap = 0.1f;
		sf::Vector2f pos(inputEnd, 0.5f);
		Recipe* r = s->recipe;
		std::vector<GUIObject*> fuelBars = {};
		float fuelSize = 0.1f;
		float fuelOffset = 0.2f;
		float fuelWidth = 0.01f;
		for (int i = 0; i < r->inputItems.size(); i++)
		{
			GUIItem* item = new GUIItem(pos, sf::Vector2f(size, size), r->data->inputTypes[i], r->inputItems[i].size());
			gui->GUIObjects.push_back(item);
			GUIPanel* bgPanel = new GUIPanel(pos + sf::Vector2f(0, fuelOffset), sf::Vector2f(fuelWidth, fuelSize), sf::Color(50, 50, 50));
			GUIPanel* colorPanel = new GUIPanel(pos + sf::Vector2f(0, fuelOffset), sf::Vector2f(fuelWidth, fuelSize), sf::Color(50, 50, 50));
			fuelBars.push_back(bgPanel);
			fuelBars.push_back(colorPanel);
			pos.x -= gap;
		}
		pos = sf::Vector2f(outputStart, pos.y);
		for (int i = 0; i < r->outputItems.size(); i++)
		{
			GUIItem* item = new GUIItem(pos, sf::Vector2f(size, size), r->data->outputTypes[i], r->outputItems[i].size());
			gui->GUIObjects.push_back(item);
			pos.x += gap;
		}
		for (int i = 0; i < fuelBars.size(); i++)
		{
			gui->GUIObjects.push_back(fuelBars[i]);
		}
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
		if (s->recipe == nullptr)
		{
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
		}
		else
		{
			int index = numBgObjs;
			for (int i = 0; i < s->recipe->inputItems.size(); i++)
			{
				dynamic_cast<GUIItem*>(gui->GUIObjects[i + index])->SetAmount(s->recipe->inputItems[i].size());
			}
			index += s->recipe->inputItems.size();
			for (int i = 0; i < s->recipe->outputItems.size(); i++)
			{
				dynamic_cast<GUIItem*>(gui->GUIObjects[i + index])->SetAmount(s->recipe->outputItems[i].size());
			}
			index += s->recipe->outputItems.size();
			float fuelSize = 0.1f;
			float fuelOffset = 0.2f;
			float fuelWidth = 0.01f;
			int fuelIndex = 0;
			for (int i = index; i < gui->GUIObjects.size(); i++)
			{
				while (!s->recipe->data->isFuels[fuelIndex])
				{
					fuelIndex++;
				}
				float currLength = s->recipe->craftTimer;
				if (currLength < 0.f)
				{
					currLength = 0.f;
				}
				currLength += s->recipe->fuelsLeft[fuelIndex];
				currLength /= s->recipe->data->fuelLengths[fuelIndex];
				float height = currLength * fuelSize;
				float pos = 0.5f + fuelOffset;
				pos += height;
				pos -= fuelSize;
				dynamic_cast<GUIPanel*>(gui->GUIObjects[i + 1])->SetColor(Lerp(sf::Color::Green, sf::Color::Red, 1.f - currLength));
				dynamic_cast<GUIPanel*>(gui->GUIObjects[i + 1])->position.y = pos;
				dynamic_cast<GUIPanel*>(gui->GUIObjects[i + 1])->size.y = height;
				i++;
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
