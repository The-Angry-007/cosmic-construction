#include "LoadGame.hpp"

LoadGame::LoadGame(GUIGalaxy* galaxy, GUIPanel* dimpanel)
{
	// saveSlots.push_back(new GUISaveSlot(sf::Vector2f(0.5f, 0.5f), ""));
	GUIObjects = {};
	{
		GUI* g = new GUI();
		g->AddObject(galaxy);
		g->AddObject(dimpanel);
		//label at the top of the screen that says "load game"
		GUILabel* newgamelabel = new GUILabel(sf::Vector2f(0.5f, 0.05f), sf::Vector2f(0.5f, 0.03f), "Load Game");
		//big box with save slots in
		GUIPanel* bg = new GUIPanel(sf::Vector2f(0.5f, 0.5f), sf::Vector2f(0.4f, 0.4f), sf::Color(189, 189, 189));
		g->AddObject(bg);
		//header
		float headerHeight = 0.04f;
		GUIPanel* headerPanel = new GUIPanel(sf::Vector2f(0.5f, 0.1f + headerHeight), sf::Vector2f(0.4f, headerHeight), sf::Color(215, 215, 215));
		GUILabel* headerText = new GUILabel(sf::Vector2f(0.3f, 0.1f + headerHeight), sf::Vector2f(0.2f, headerHeight - 0.01f), "Save Files");
		headerText->SetColor(sf::Color::Black);
		headerText->origin = sf::Vector2f(0.f, 0.5f);
		g->AddObject(headerPanel);
		g->AddObject(headerText);
		this->GUIObjects = g->GUIObjects;
	}
}

void LoadGame::Update(float dt)
{
	for (uint i = 0; i < GUIObjects.size(); i++)
	{
		GUIObjects[i]->Update(dt);
	}
}
void LoadGame::Render()
{
	for (uint i = 0; i < GUIObjects.size(); i++)
	{
		GUIObjects[i]->Render();
	}
}