#include "SiloMenu.hpp"
#include "Main.hpp"
#include "binds.hpp"
SiloMenu::SiloMenu(StorageSilo* s)
{
	this->silo = s;
	// items.push_back(GUIItem(
	// 	sf::Vector2f(0.5f, 0.5f),
	// 	sf::Vector2f(0.3f, 0.3f),
	// 	0,
	// 	1));
	GUIPanel* p = new GUIPanel(sf::Vector2f(0.5f, 0.5f), sf::Vector2f(0.4f, 0.4f), sf::Color(150, 150, 150));

	GUIObjects.push_back(p);
	GUIPanel* topPanel = new GUIPanel(sf::Vector2f(0.5f, 0.13f), sf::Vector2f(0.4f, 0.03f), sf::Color(125, 125, 125));
	GUIObjects.push_back(topPanel);
	GUILabel* topLabel = new GUILabel(sf::Vector2f(0.5f, 0.13f), sf::Vector2f(0.9f, 0.025f), "Storage Silo");
	topLabel->SetColor(sf::Color::Black);
	GUIObjects.push_back(topLabel);
	game->inMenu = true;
}

void SiloMenu::Update(float dt)
{
	bool changed = false;
	if (items.size() != silo->itemIDs.size())
	{
		changed = true;
	}
	else
		for (uint i = 0; i < items.size(); i++)
		{
			if (silo->itemIDs[i] != items[i].typeID || silo->itemQuantities[i] != items[i].amount)
			{
				changed = true;
			}
		}
	if (changed)
	{
		items = {};
		for (uint i = 0; i < silo->itemIDs.size(); i++)
		{
			items.push_back(GUIItem(sf::Vector2f(0.f, 0.f), sf::Vector2f(1.f, 1.f), silo->itemIDs[i], silo->itemQuantities[i]));
		}
	}

	for (int i = 0; i < items.size(); i++)
	{
		items[i].Update(dt);
	}
	InputHandler::mouseIsBlocked = true;
	if (InputHandler::pressed(binds::CloseInventory))
	{
		InputHandler::RemovePressed(binds::CloseInventory);
		InputHandler::RemoveDown(binds::CloseInventory);
		guihandler.guis.erase(guihandler.guis.end() - 1);
		game->inMenu = false;
		delete this;
	}
}
void SiloMenu::Render()
{
	for (uint i = 0; i < GUIObjects.size(); i++)
	{
		GUIObjects[i]->Render();
	}
	sf::RenderTexture text;
	text.create(width, height);
	text.setView(sf::View(sf::Vector2f(width / 2.f, height / 2.f), sf::Vector2f(width, height)));
	text.clear(sf::Color::Transparent);
	sf::Vector2f gap(0.1f, 0.1f);
	float size = 0.05f;
	sf::Vector2f spos(0.1f + size, 0.16f + size);
	// spos += gap;
	sf::Vector2f pos = spos;
	for (int i = 0; i < items.size(); i++)
	{
		//arranging items
		items[i].position = pos;
		items[i].size = sf::Vector2f(size, size);
		items[i].RenderToTexture(&text);
		pos.x += gap.x;
		if (pos.x > 1 - spos.x)
		{
			pos.x = spos.x;
			pos.y += gap.y;
		}
	}
	text.display();
	sf::Sprite s(text.getTexture());
	sf::IntRect bounds(sf::Vector2i(width * 0.1f, height * 0.16f), sf::Vector2i(width * 0.8f, height * (0.8f - 0.06f)));
	s.setTextureRect(bounds);
	s.setPosition(bounds.left, bounds.top);
	s.setOrigin(0.f, 0.f);

	window->draw(s);
}