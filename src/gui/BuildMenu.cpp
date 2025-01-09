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
	infoLabel = new GUILabel(sf::Vector2f(0.9f - infoSize / 2.f, 0.1f + height), sf::Vector2f(infoSize / 2.f, height * 0.9f), "Info");
	infoLabel->SetColor(sf::Color::Black);
	infoLabel->origin = sf::Vector2f(0.5f, 0.f);
	bg = new GUIPanel(sf::Vector2f(0.5f, 0.5f), sf::Vector2f(0.4f, 0.4f), sf::Color(150, 150, 150));
	menus.push_back({});
	menus.push_back({});
	menus.push_back({});
	typeIDs = { { 0, 0, 1 }, { 0 }, { 0 } };
	std::vector<std::vector<std::vector<int>>> frames = { { { 0 }, { 1 }, { 0, 1 } }, { { 2 } }, { { 1 } } };
	for (int j = 0; j < 3; j++)
	{
		sf::Vector2f imageSize(0.05f, 0.05f);
		float textHeight = 0.01f;
		float gapSize = 0.03f;

		sf::Vector2f startPos = sf::Vector2f(0.1f, 0.1f + height * 2.f + gapSize) + imageSize;
		sf::Vector2f pos = startPos;
		for (int i = 0; i < typeIDs[j].size(); i++)
		{
			GUIStructure* s = new GUIStructure(pos, imageSize, typeIDs[j][i], frames[j][i]);

			s->Render();

			sf::Vector2f textPos(0.f, s->actualSize.y / 2.f + textHeight);
			textPos += pos;
			sf::Vector2f textSize(s->actualSize.x / 2.f, textHeight);
			std::string text = ResourceHandler::structureTable->GetValue("Name", typeIDs[j][i]);
			GUILabel* l = new GUILabel(textPos, textSize, text);
			l->SetColor(sf::Color::Black);
			menus[j].push_back(s);
			menus[j].push_back(l);
			pos.x += s->actualSize.x;
			pos.x += gapSize;
			if (pos.x + s->actualSize.x > 0.9f - infoSize)
			{
				pos.x = startPos.x;
				pos.y += s->actualSize.y + textHeight * 2.f + gapSize;
			}
		}
	}
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
	for (int i = 0; i < menus[currentTab].size(); i++)
	{
		menus[currentTab][i]->Update(dt);
		if (i % 2 == 0)
		{
			if (menus[currentTab][i]->isClicked())
			{
				game->toolHandler->placeType = typeIDs[currentTab][i / 2];
				guihandler.OpenGUI(5);
				game->inMenu = false;
				InputHandler::RemoveMbPressed(sf::Mouse::Button::Left);
				InputHandler::RemoveMbDown(sf::Mouse::Button::Left);
			}
		}
	}
	infoLabel->Update(dt);
}
void BuildMenu::Render()
{
	bg->Render();
	for (int i = 0; i < tabs.size(); i++)
	{
		tabs[i]->Render();
	}

	for (int i = 0; i < menus[currentTab].size(); i++)
	{
		menus[currentTab][i]->Render();
	}
	infoLabel->Render();
}