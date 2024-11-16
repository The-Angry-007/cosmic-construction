#include "../gui.hpp"
Settings::Settings()
{
	//this is not used, it is just part of the base class
	GUIObjects = {};

	bgGUI = new GUI();
	{
		GUIPanel* p = new GUIPanel(sf::Vector2f(0.5f, 0.5f), sf::Vector2f(0.4f, 0.4f), sf::Color(100, 100, 100));
		bgGUI->AddObject(p);
	}
	pageGuis = {};
	pageGuis.push_back(new GUI());
	currentGUI = 0;
}

void Settings::Update(float dt)
{
	behindGUI->Update(dt);
	bgGUI->Update(dt);
	pageGuis[currentGUI]->Update(dt);
}

void Settings::Render()
{
	behindGUI->Render();
	// bgGUI->Render();
	// pageGuis[currentGUI]->Render();
}

Settings::~Settings()
{
	delete behindGUI;
	delete bgGUI;
	for (uint i = 0; i < pageGuis.size(); i++)
	{
		delete pageGuis[i];
	}
}