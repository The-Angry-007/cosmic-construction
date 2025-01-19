#include "BuildMenu.hpp"
#include "GUIStructure.hpp"
#include "Main.hpp"
#include "game/ResourceHandler.hpp"
#include "utils.hpp"
BuildMenu::BuildMenu()
{
	std::vector<std::string> titles = { "Transport", "Production", "Storage" };
	float infoSize = 0.15f;
	float height = 0.03f;

	for (int i = 0; i < 3; i++)
	{
		sf::Vector2f size = sf::Vector2f((0.8f - infoSize) / 3.f / 2.f, height);
		sf::Vector2f pos = sf::Vector2f(0.1f + size.x * (i * 2 + 1), 0.1f + height);
		GUILabel* l = new GUILabel(pos, size * 0.9f, titles[i]);
		l->SetColor(sf::Color::Black);
		GUIPanel* bgP = new GUIPanel(pos, size, sf::Color(150, 150, 150));
		GUIButton* b = new GUIButton(pos, size, bgP, l);
		tabs.push_back(b);
	}
	SetTab(0);
	infoBG = new GUIPanel(sf::Vector2f(0.9f - infoSize / 2.f, 0.5f), sf::Vector2f(infoSize / 2.f, 0.4f), sf::Color(120, 120, 120));
	infoLabel = new GUILabel(sf::Vector2f(0.9f - infoSize / 2.f, 0.1f + height), sf::Vector2f(infoSize / 2.f, height * 0.9f), "Info");
	infoLabel->SetColor(sf::Color::Black);
	infoLabel->origin = sf::Vector2f(0.5f, 0.f);
	bg = new GUIPanel(sf::Vector2f(0.5f, 0.5f), sf::Vector2f(0.4f, 0.4f), sf::Color(150, 150, 150));
	menus.push_back({});
	menus.push_back({});
	menus.push_back({});
	typeIDs = { { 0 }, { 3, 4, 6 }, { 1 } };
	std::vector<std::vector<std::vector<int>>> frames = { { { 0 } }, { { 4 * 15 }, { 0 }, { 0 } }, { { 0, 1 } } };
	for (int j = 0; j < 3; j++)
	{
		sf::Vector2f imageSize(0.05f, 0.05f);
		float gapSize = 0.03f;

		sf::Vector2f startPos = sf::Vector2f(0.1f, 0.1f + height * 2.f + gapSize) + imageSize;
		sf::Vector2f pos = startPos;
		for (int i = 0; i < typeIDs[j].size(); i++)
		{
			GUIStructure* s = new GUIStructure(pos, imageSize, typeIDs[j][i], frames[j][i]);

			s->Render();

			menus[j].push_back(s);
			pos.x += s->actualSize.x;
			pos.x += gapSize;
			if (pos.x + s->actualSize.x > 0.9f - infoSize)
			{
				pos.x = startPos.x;
				pos.y += s->actualSize.y + gapSize;
			}
		}
	}
	float bottom = 0.5f;
	float x = 0.9f - infoSize / 2.f;
	float w = infoSize / 2.f - 0.01f;
	infoText = new GUILabel(sf::Vector2f(x, (0.1f + height * 2.f + bottom) / 2.f), sf::Vector2f(w, (bottom - (0.1f + 2 * height)) / 2.f), "");
	infoText->origin = sf::Vector2f(0.f, 0.f);
	infoText->SetColor(sf::Color::Black);
	costLabel = new GUILabel(sf::Vector2f(x, bottom + height), sf::Vector2f(w, height), "Cost");
	costLabel->SetColor(sf::Color::Black);
	costText = new GUILabel(sf::Vector2f(x, (0.9f + bottom + 2 * height) / 2.f + 0.01f), sf::Vector2f(w, (0.9f - (bottom + 2 * height)) / 2.f - 0.005f), "");
	costText->SetColor(sf::Color::Black);
	costText->origin = sf::Vector2f(0.f, 0.f);
}

void BuildMenu::SetTab(int tab)
{
	currentTab = tab;
	for (int i = 0; i < 3; i++)
	{
		sf::Color col(100, 100, 100);
		if (i == tab)
		{
			col = sf::Color(150, 150, 150);
		}

		dynamic_cast<GUIPanel*>(tabs[i]->bgObj)->SetColor(col);
	}
}

void BuildMenu::Update(float dt)
{
	bg->Update(dt);
	for (int i = 0; i < tabs.size(); i++)
	{
		tabs[i]->Update(dt);
		if (tabs[i]->isClicked())
		{
			SetTab(i);
		}
	}
	infoText->value = "";
	costText->value = "";
	for (int i = 0; i < menus[currentTab].size(); i++)
	{
		menus[currentTab][i]->Update(dt);

		if (menus[currentTab][i]->isClicked())
		{
			game->toolHandler->placeType = typeIDs[currentTab][i];
			guihandler.OpenGUI(5);
			game->inMenu = false;
			game->toolHandler->selectedTool = 0;
			InputHandler::RemoveMbPressed(sf::Mouse::Button::Left);
			InputHandler::RemoveMbDown(sf::Mouse::Button::Left);
		}
		else if (menus[currentTab][i]->isBlockingMouse())
		{
			infoText->value = ResourceHandler::structureTable->GetValue("Name", typeIDs[currentTab][i]);
			infoText->value += "\n" + ResourceHandler::structureTable->GetValue("Description", typeIDs[currentTab][i]);
			infoText->DoWrapping(10);
			costText->value = "";
			auto cost = ResourceHandler::GetCost(typeIDs[currentTab][i]);
			for (int i = 1; i < cost.size(); i += 2)
			{
				if (i != 1)
				{
					costText->value += "\n";
				}
				costText->value += ResourceHandler::itemTable->GetValue("Name", cost[i]);
				costText->value += " x ";
				costText->value += std::to_string(cost[i + 1]);
			}
		}
	}
	infoBG->Update(dt);
	infoLabel->Update(dt);
	infoText->Update(dt);
	costLabel->Update(dt);
	costText->Update(dt);
}
void BuildMenu::Render()
{
	bg->Render();
	infoBG->Render();
	for (int i = 0; i < tabs.size(); i++)
	{
		tabs[i]->Render();
	}

	for (int i = 0; i < menus[currentTab].size(); i++)
	{
		menus[currentTab][i]->Render();
	}
	infoText->Render();
	infoLabel->Render();
	costLabel->Render();
	costText->Render();
}