#include "Tutorial.hpp"
#include "Main.hpp"
#include "binds.hpp"
#include "gui/BuildMenu.hpp"
#include "saving.hpp"
#include "utils.hpp"
Tutorial::Tutorial()
{
	gui = nullptr;
	std::string scriptString = SaveHandler::ReadData("content\\resources\\text files\\tutorial.txt");
	script = Split(scriptString, '\n');
	int numPhases = script.size();
	validCodes = {};
	for (int i = 0; i < numPhases; i++)
	{
		validCodes.push_back({ binds::Pause });
	}
	validCodes[3].push_back(binds::UseTool);
	validCodes[5].push_back(binds::UseTool);
	validCodes[6].push_back(binds::UseTool);
	validCodes[6].push_back(sf::Keyboard::Key::LShift + 1);
	validCodes[8].push_back(binds::CloseInventory);
	validCodes[9].push_back(binds::CloseInventory);
	validCodes[9].push_back(binds::UseTool);
	validCodes[10].push_back(binds::UseTool);
	validCodes[12].push_back(binds::CloseInventory);
	validCodes[13].push_back(binds::CloseInventory);
	validCodes[13].push_back(binds::UseTool);
	validCodes[14].push_back(binds::UseTool);
	validCodes[15].push_back(binds::RotateStructure);
	validCodes[19].push_back(binds::CloseInventory);
	validCodes[20].push_back(binds::CloseInventory);
	validCodes[20].push_back(binds::UseTool);
	validCodes[22].push_back(binds::UseTool);
	validCodes[22].push_back(binds::CloseInventory);
	validCodes[22].push_back(binds::RotateStructure);
	validCodes[22].push_back(sf::Keyboard::Key::LShift + 1);
	validCodes[22].push_back(binds::Tool2);
	validCodes[22].push_back(binds::Tool3);
	validCodes[29].push_back(binds::Tool3);
	validCodes[29].push_back(binds::Tool2);
	validCodes[29].push_back(binds::CloseInventory);
	validCodes[29].push_back(binds::RotateStructure);
	validCodes[29].push_back(sf::Keyboard::Key::LShift + 1);
	validCodes[29].push_back(binds::UseTool);
	SwitchPhase(0);
	skippables = {};
	for (int i = 0; i < numPhases; i++)
	{
		if (script[i].back() == '>')
		{
			skippables.push_back(true);
		}
		else
		{
			skippables.push_back(false);
		}
	}
	game->ActivePlanet()->camera.targetZoom = 0.4f;
}

void Tutorial::SwitchPhase(int phase)
{
	if (gui != nullptr)
	{
		delete gui;
	}
	currentPhase = phase;
	// skippables = { true, true, true, false, true, false, false };
	gui = new GUI();
	float ypos = 0.12f;
	GUIPanel* outlineBG = new GUIPanel(sf::Vector2f(0.5f, ypos), sf::Vector2f(0.33f, 0.1f), sf::Color(50, 50, 50));
	GUIPanel* bg = new GUIPanel(sf::Vector2f(0.5f, ypos), sf::Vector2f(0.32f, 0.09f), sf::Color(150, 150, 150));
	GUILabel* label = new GUILabel(sf::Vector2f(0.5f, ypos), sf::Vector2f(0.3f, 0.08f), script[currentPhase]);
	label->SetColor(sf::Color::Black);
	label->DoWrapping(70);
	gui->AddObject(outlineBG);
	gui->AddObject(bg);
	gui->AddObject(label);
	if (phase == 3)
	{
		game->toolHandler->selectedTool = 2;
	}
	else if (phase == 5)
	{
		game->toolHandler->selectedTool = 1;
	}
	GUIImage* skipImage = new GUIImage(sf::Vector2f(0.92f, 0.9f), sf::Vector2f(0.08f, 0.04f), "content/resources/images/buttonBezels.png");
	GUILabel* skipLabel = new GUILabel(sf::Vector2f(0.92f, 0.9f), sf::Vector2f(0.075f, 0.035f), "skip tutorial");
	GUIButton* skipButton = new GUIButton(sf::Vector2f(0.92f, 0.9f), sf::Vector2f(0.08f, 0.04f), skipImage, skipLabel);
	skipLabel->SetColor(sf::Color::Black);
	std::function<void()> endFunc = std::bind(&Tutorial::EndTutorial, this);
	skipButton->clickFunc = endFunc;
	gui->AddObject(skipButton);
}

void Tutorial::Update(float dt)
{

	if (gui != nullptr)
	{
		gui->Update(dt);
		float ypos = 0.12f;
		if (game->inMenu || guihandler.activeGui != 5)
		{
			ypos = 1.f - ypos;
		}
		for (int i = 0; i < 3; i++)
		{
			gui->GUIObjects[i]->position.y = ypos;
		}
	}
	//skip tutorial button was clicked
	if (tutorial == nullptr)
	{
		return;
	}
	if (skippables[currentPhase] && InputHandler::keyPressed(sf::Keyboard::Key::Tab))
	{
		if (currentPhase == 35)
		{
			EndTutorial();
			return;
		}
		SwitchPhase(currentPhase + 1);
	}
	Planet& p = game->planets[game->activePlanet];
	if (currentPhase == 3 && p.StructuresInArea({ 0, 0 }, { 31, 31 }).size() == 1)
	{
		SwitchPhase(4);
	}
	if (currentPhase == 5)
	{
		StorageSilo* s = dynamic_cast<StorageSilo*>(p.structures[p.StructureInPos({ 16, 16 })]);
		if (s->itemIDs.size() > 1 || s->itemQuantities[0] > 20)
		{
			SwitchPhase(6);
		}
	}
	if (currentPhase == 6)
	{
		bool skip = true;
		for (int i = 0; i < p.items.size(); i++)
		{
			if (!p.items[i].isDeleted)
			{
				skip = false;
				break;
			}
		}
		if (skip)
		{
			SwitchPhase(7);
		}
	}
	if (currentPhase == 8)
	{
		if (InputHandler::pressed(binds::CloseInventory))
		{
			SwitchPhase(9);
		}
	}
	if (currentPhase == 9)
	{
		if (game->toolHandler->placeType == 4)
		{
			SwitchPhase(10);
		}
	}
	if (currentPhase == 10)
	{
		std::vector<int> structures = p.StructuresInArea({ 0, 0 }, { 32, 32 });
		for (int i = 0; i < structures.size(); i++)
		{
			if (p.structures[structures[i]]->typeID == 4)
			{
				SwitchPhase(11);
				break;
			}
		}
	}
	if (currentPhase == 12)
	{
		if (InputHandler::pressed(binds::CloseInventory))
		{
			SwitchPhase(13);
		}
	}
	if (currentPhase == 13)
	{
		if (game->toolHandler->placeType == 3)
		{
			SwitchPhase(14);
		}
	}
	if (currentPhase == 14)
	{
		//find sapling planter
		sf::Vector2i pos(0, 0);
		std::vector<int> structures = p.StructuresInArea({ 0, 0 }, { 32, 32 });
		for (int i = 0; i < structures.size(); i++)
		{
			if (p.structures[structures[i]]->typeID == 4)
			{
				pos = p.structures[structures[i]]->position;
				break;
			}
		}
		//find tree chopper in neighbouring square
		for (int i = 0; i < 4; i++)
		{
			sf::Vector2i newPos = pos + CONVEYOR_OFFSETS[i];
			int index = p.StructureInPos(newPos);
			if (index != -1 && p.structures[index]->typeID == 3)
			{
				SwitchPhase(15);
			}
		}
	}
	if (currentPhase == 15)
	{
		game->toolHandler->selectedTool = 1;
		//find sapling planter
		sf::Vector2i pos(0, 0);
		std::vector<int> structures = p.StructuresInArea({ 0, 0 }, { 32, 32 });
		for (int i = 0; i < structures.size(); i++)
		{
			if (p.structures[structures[i]]->typeID == 4)
			{
				pos = p.structures[structures[i]]->position;
				break;
			}
		}
		//find tree chopper in neighbouring square
		for (int i = 0; i < 4; i++)
		{
			sf::Vector2i newPos = pos + CONVEYOR_OFFSETS[i];
			int index = p.StructureInPos(newPos);
			if (index != -1 && p.structures[index]->typeID == 3 && p.structures[index]->direction == (i + 2) % 4)
			{
				SwitchPhase(16);
			}
		}
	}
	if (currentPhase == 19)
	{
		if (InputHandler::pressed(binds::CloseInventory))
		{
			SwitchPhase(20);
		}
	}
	if (currentPhase == 20)
	{
		if (game->toolHandler->placeType == 0)
		{
			SwitchPhase(21);
		}
	}
	if (currentPhase == 22)
	{
		auto numWood = p.TallyResources({ 0, 0 }, { 0 });
		if (numWood[0] >= 30)
		{
			SwitchPhase(23);
		}
	}
	if (currentPhase == 29)
	{
		auto tally = p.TallyResources({ 0, 0 }, { 1, 2 });
		if (tally[0] >= 15 && tally[1] >= 5)
		{
			SwitchPhase(30);
		}
	}

	if (!game->paused)
	{
		LimitInputs();
	}
}
void Tutorial::Render()
{
	if (gui == nullptr)
	{
		return;
	}
	sf::View currentView = window->getView();
	sf::View GUIView(sf::FloatRect(0.f, 0.f, width, height));
	window->setView(GUIView);
	gui->Render();

	window->setView(currentView);
}

void Tutorial::LimitInputs()
{
	for (int i = 0; i < InputHandler::keysPressed.size(); i++)
	{
		int code = binds::keyToCode(InputHandler::keysPressed[i]);
		bool valid = false;
		for (int j = 0; j < validCodes[currentPhase].size(); j++)
		{
			if (validCodes[currentPhase][j] == code)
			{
				valid = true;
				break;
			}
		}
		if (!valid)
		{
			InputHandler::keysPressed.erase(InputHandler::keysPressed.begin() + i);
			i--;
		}
	}
	for (int i = 0; i < InputHandler::keysDown.size(); i++)
	{
		int code = binds::keyToCode(InputHandler::keysDown[i]);
		bool valid = false;
		for (int j = 0; j < validCodes[currentPhase].size(); j++)
		{
			if (validCodes[currentPhase][j] == code)
			{
				valid = true;
				break;
			}
		}
		if (!valid)
		{
			InputHandler::keysDown.erase(InputHandler::keysDown.begin() + i);
			i--;
		}
	}

	for (int i = 0; i < InputHandler::mouseButtonsPressed.size(); i++)
	{
		int code = binds::buttonToCode(InputHandler::mouseButtonsPressed[i]);
		bool valid = false;
		for (int j = 0; j < validCodes[currentPhase].size(); j++)
		{
			if (validCodes[currentPhase][j] == code)
			{
				valid = true;
				break;
			}
		}
		if (!valid)
		{
			InputHandler::mouseButtonsPressed.erase(InputHandler::mouseButtonsPressed.begin() + i);
			i--;
		}
	}
	for (int i = 0; i < InputHandler::mouseButtonsDown.size(); i++)
	{
		int code = binds::buttonToCode(InputHandler::mouseButtonsDown[i]);
		bool valid = false;
		for (int j = 0; j < validCodes[currentPhase].size(); j++)
		{
			if (validCodes[currentPhase][j] == code)
			{
				valid = true;
				break;
			}
		}
		if (!valid)
		{
			InputHandler::mouseButtonsDown.erase(InputHandler::mouseButtonsDown.begin() + i);
			i--;
		}
	}
}

void Tutorial::EndTutorial()
{
	tutorial = nullptr;
	delete this;
}

Tutorial::~Tutorial()
{
	if (gui != nullptr)
	{
		delete gui;
	}
}