#include "../gui.hpp"
#include "Main.hpp"
Settings::Settings()
{
	//this is not used, it is just part of the base class
	GUIObjects = {};

	bgGUI = new GUI();
	{
		GUIPanel* dimmer = new GUIPanel(sf::Vector2f(0.5f, 0.5f), sf::Vector2f(0.5f, 0.5f), sf::Color(0, 0, 0, 150));
		bgGUI->AddObject(dimmer);
		GUIPanel* p = new GUIPanel(sf::Vector2f(0.5f, 0.5f), sf::Vector2f(0.4f, 0.4f), sf::Color(150, 150, 150));

		bgGUI->AddObject(p);
		GUIPanel* topPanel = new GUIPanel(sf::Vector2f(0.5f, 0.13f), sf::Vector2f(0.4f, 0.03f), sf::Color(125, 125, 125));
		bgGUI->AddObject(topPanel);
		GUILabel* optionsLabel = new GUILabel(sf::Vector2f(0.5f, 0.13f), sf::Vector2f(0.9f, 0.025f), "Options");
		optionsLabel->SetColor(sf::Color::Black);
		bgGUI->AddObject(optionsLabel);
	}
	pageGuis = {};
	{
		GUI* g = new GUI();
		GUIImage* i = new GUIImage(sf::Vector2f(0.33f, 0.22f), sf::Vector2f(0.15f, 0.04f), "resources/images/buttonBezels.png");
		GUILabel* l = new GUILabel(sf::Vector2f(0.33f, 0.22f), sf::Vector2f(0.15f - 0.01f, 0.04f - 0.01f), "Controls");
		l->SetColor(sf::Color::Black);
		GUIButton* b = new GUIButton(sf::Vector2f(0.33f, 0.22f), sf::Vector2f(0.15f, 0.04f), i, l);
		g->AddObject(b);

		GUIImage* i2 = new GUIImage(sf::Vector2f(0.67f, 0.22f), sf::Vector2f(0.15f, 0.04f), "resources/images/buttonBezels.png");
		GUILabel* l2 = new GUILabel(sf::Vector2f(0.67f, 0.22f), sf::Vector2f(0.15f - 0.01f, 0.04f - 0.01f), "Audio");
		l2->SetColor(sf::Color::Black);
		GUIButton* b2 = new GUIButton(sf::Vector2f(0.67f, 0.22f), sf::Vector2f(0.15f, 0.04f), i2, l2);
		g->AddObject(b2);

		GUILabel* l3 = new GUILabel(sf::Vector2f(0.5f, 0.3f), sf::Vector2f(0.35f, 0.025f), "Framerate:");
		l3->SetColor(sf::Color::Black);
		g->AddObject(l3);
		GUIPanel* sliderBG = new GUIPanel(sf::Vector2f(0.5f, 0.37f), sf::Vector2f(0.35f, 0.015f), sf::Color(50, 50, 50));
		GUIImage* sliderKnob = new GUIImage(sf::Vector2f(0.f, 0.f), sf::Vector2f(0.025f, 0.025f), "resources/images/squareButton.png");
		sliderKnob->keepAspectRatio = true;
		GUISlider* s = new GUISlider(sf::Vector2f(0.5f, 0.37f), sf::Vector2f(0.35f, 0.015f), sliderKnob, sliderBG, nullptr);
		g->AddObject(s);
		s->value = 0.f;

		GUILabel* l4 = new GUILabel(sf::Vector2f(0.5f, 0.45f), sf::Vector2f(0.35f, 0.025f), "Autosave Interval:");
		l4->SetColor(sf::Color::Black);
		g->AddObject(l4);
		GUIPanel* sliderBG2 = new GUIPanel(sf::Vector2f(0.5f, 0.53f), sf::Vector2f(0.35f, 0.015f), sf::Color(50, 50, 50));
		GUIImage* sliderKnob2 = new GUIImage(sf::Vector2f(0.f, 0.f), sf::Vector2f(0.025f, 0.025f), "resources/images/squareButton.png");
		sliderKnob2->keepAspectRatio = true;
		GUISlider* s2 = new GUISlider(sf::Vector2f(0.5f, 0.53f), sf::Vector2f(0.35f, 0.015f), sliderKnob2, sliderBG2, nullptr);
		g->AddObject(s2);

		GUIImage* i3 = new GUIImage(sf::Vector2f(0.5f, 0.75f), sf::Vector2f(0.3f, 0.04f), "resources/images/buttonBezels.png");
		GUILabel* l5 = new GUILabel(sf::Vector2f(0.5f, 0.75f), sf::Vector2f(0.3f - 0.01f, 0.04f - 0.01f), "Go Back");
		l5->SetColor(sf::Color::Black);
		GUIButton* b3 = new GUIButton(sf::Vector2f(0.5f, 0.75f), sf::Vector2f(0.3f, 0.04f), i3, l5);
		g->AddObject(b3);
		b3->clickFunc = std::bind(&GUIHandler::GoBack, &guihandler);

		pageGuis.push_back(g);
	}
	currentGUI = 0;
}

void Settings::Update(float dt)
{
	behindGUI->Update(dt);
	bgGUI->Update(dt);
	GUI* cGUI = pageGuis[currentGUI];
	cGUI->Update(dt);
	if (currentGUI == 0)
	{
		GUISlider* s1 = dynamic_cast<GUISlider*>(cGUI->GUIObjects[3]);
		GUILabel* l1 = dynamic_cast<GUILabel*>(cGUI->GUIObjects[2]);
		int min = 10;
		int max = 250;
		int increments = 10;
		int steps = (max - min) / increments + 2;
		s1->value = round(s1->value * steps) / steps;
		s1->AdjustFromVal();
		if (s1->value < 0.01f)
		{
			l1->value = "Framerate: Vertical Sync enabled";
			window->setVerticalSyncEnabled(true);
			window->setFramerateLimit(1000);
			framerate = -1;
		}
		else if (s1->value > 0.99f)
		{
			l1->value = "Framerate: Unlimited";
			window->setVerticalSyncEnabled(false);
			window->setFramerateLimit(10000);
			framerate = 10000;
		}
		else
		{
			framerate = round(min + (max - min) * (s1->value - 1.f / steps) / (1.f - (1.f / steps) * 2.f));
			l1->value = "Framerate: " + std::to_string(framerate);
			window->setVerticalSyncEnabled(false);
			window->setFramerateLimit(framerate);
		}
	}
}

void Settings::Render()
{
	behindGUI->Render();
	bgGUI->Render();
	pageGuis[currentGUI]->Render();
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
