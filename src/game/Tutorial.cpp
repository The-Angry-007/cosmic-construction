#include "Tutorial.hpp"
#include "Main.hpp"
#include "binds.hpp"
#include "saving.hpp"
#include "utils.hpp"
Tutorial::Tutorial()
{
	gui = nullptr;
	std::string scriptString = SaveHandler::ReadData("content\\resources\\text files\\tutorial.txt");
	script = Split(scriptString, '\n');
	int numPhases = 4;
	validCodes = {};
	for (int i = 0; i < numPhases; i++)
	{
		validCodes.push_back({});
	}
	validCodes[3].push_back(binds::UseTool);
	SwitchPhase(0);
}

void Tutorial::SwitchPhase(int phase)
{
	if (gui != nullptr)
	{
		delete gui;
	}
	currentPhase = phase;
	skippables = { true, true, true, false };
	gui = new GUI();
	GUIPanel* bg = new GUIPanel(sf::Vector2f(0.5f, 0.85f), sf::Vector2f(0.33f, 0.13f), sf::Color(150, 150, 150));
	GUILabel* label = new GUILabel(sf::Vector2f(0.5f, 0.85f), sf::Vector2f(0.3f, 0.1f), script[currentPhase]);
	label->SetColor(sf::Color::Black);
	label->DoWrapping(70);
	gui->AddObject(bg);
	gui->AddObject(label);
	if (phase == 3)
	{
		game->toolHandler->selectedTool = 2;
	}
}

void Tutorial::Update(float dt)
{
	if (gui != nullptr)
	{
		gui->Update(dt);
	}
	if (skippables[currentPhase] && InputHandler::keyPressed(sf::Keyboard::Key::Tab))
	{
		SwitchPhase(currentPhase + 1);
	}
	LimitInputs();
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