#include "BuildMenu.hpp"
#include "GUIStructure.hpp"
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
	menus[0].push_back(new GUIStructure(sf::Vector2f(0.5f, 0.5f), sf::Vector2f(0.2f, 0.2f), 0, { 0 }));
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