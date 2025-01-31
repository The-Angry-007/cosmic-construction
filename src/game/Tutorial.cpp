#include "Tutorial.hpp"
#include "Main.hpp"
#include "saving.hpp"
#include "utils.hpp"
Tutorial::Tutorial()
{
	gui = nullptr;
	std::string scriptString = SaveHandler::ReadData("content\\resources\\text files\\tutorial.txt");
	script = Split(scriptString, '\n');
	int numPhases = 1;
	validCodes = {};
	for (int i = 0; i < numPhases; i++)
	{
		validCodes.push_back({});
	}
	SwitchPhase(0);
}

void Tutorial::SwitchPhase(int phase)
{
	if (gui != nullptr)
	{
		delete gui;
	}
	currentPhase = phase;
	skippables = { true, false };
	gui = new GUI();
	GUIPanel* bg = new GUIPanel(sf::Vector2f(0.5f, 0.85f), sf::Vector2f(0.33f, 0.13f), sf::Color(150, 150, 150));
	GUILabel* label = new GUILabel(sf::Vector2f(0.5f, 0.85f), sf::Vector2f(0.3f, 0.1f), script[currentPhase]);
	label->SetColor(sf::Color::Black);
	label->DoWrapping(70);
	gui->AddObject(bg);
	gui->AddObject(label);
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