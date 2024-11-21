#include "LoadGame.hpp"
#include "Main.hpp"

LoadGame::LoadGame(GUIGalaxy* galaxy, GUIPanel* dimpanel)
{
	saveSlots.push_back(new GUISaveSlot(sf::Vector2f(0.5f, 0.5f), ""));
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
	std::cout << "updating" << std::endl;

	for (uint i = 0; i < GUIObjects.size(); i++)
	{
		GUIObjects[i]->Update(dt);
	}
	for (uint i = 0; i < saveSlots.size(); i++)
	{
		saveSlots[i]->Update(dt);
	}
}
void LoadGame::Render()
{
	std::cout << "rendering" << std::endl;

	for (uint i = 0; i < GUIObjects.size(); i++)
	{
		GUIObjects[i]->Render();
	}
	std::cout << "starting drawing texture" << std::endl;

	sf::RenderTexture t;
	t.create(width, height);
	t.clear(sf::Color::Transparent);
	for (uint i = 0; i < saveSlots.size(); i++)
	{
		saveSlots[i]->RenderToTexture(&t);
	}
	t.display();
	std::cout << "finished drawing to texture" << std::endl;
	sf::Sprite s;
	// s.setPosition(0.1f * width, 0.1f * height);
	s.setTexture(t.getTexture());
	// s.setTextureRect(sf::IntRect(sf::Vector2i(0.5f * width, 0.5f * height), sf::Vector2i(0.8f * width, 0.8f * height)));
	window->draw(s);
	std::cout << "drawn to window" << std::endl;
}