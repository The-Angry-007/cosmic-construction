#include "../gui.hpp"
#include "InputHandler.hpp"
#include "Main.hpp"
#include "binds.hpp"

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
	}
	pageGuis = {};
	//FIRST PAGE
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
		s->minVal = 0;
		s->maxVal = 260;
		s->numSteps = 26;

		GUILabel* l4 = new GUILabel(sf::Vector2f(0.5f, 0.45f), sf::Vector2f(0.35f, 0.025f), "Autosave Interval:");
		l4->SetColor(sf::Color::Black);
		g->AddObject(l4);
		GUIPanel* sliderBG2 = new GUIPanel(sf::Vector2f(0.5f, 0.53f), sf::Vector2f(0.35f, 0.015f), sf::Color(50, 50, 50));
		GUIImage* sliderKnob2 = new GUIImage(sf::Vector2f(0.f, 0.f), sf::Vector2f(0.025f, 0.025f), "resources/images/squareButton.png");
		sliderKnob2->keepAspectRatio = true;
		GUISlider* s2 = new GUISlider(sf::Vector2f(0.5f, 0.53f), sf::Vector2f(0.35f, 0.015f), sliderKnob2, sliderBG2, nullptr);
		g->AddObject(s2);
		s2->minVal = 5;
		s2->maxVal = 65;
		s2->numSteps = 12;
		s2->value = 0.f;

		GUIImage* i3 = new GUIImage(sf::Vector2f(0.5f, 0.75f), sf::Vector2f(0.3f, 0.04f), "resources/images/buttonBezels.png");
		GUILabel* l5 = new GUILabel(sf::Vector2f(0.5f, 0.75f), sf::Vector2f(0.3f - 0.01f, 0.04f - 0.01f), "Go Back");
		l5->SetColor(sf::Color::Black);
		GUIButton* b3 = new GUIButton(sf::Vector2f(0.5f, 0.75f), sf::Vector2f(0.3f, 0.04f), i3, l5);
		g->AddObject(b3);
		b3->clickFunc = std::bind(&GUIHandler::GoBack, &guihandler);
		GUILabel* optionsLabel = new GUILabel(sf::Vector2f(0.5f, 0.13f), sf::Vector2f(0.9f, 0.025f), "Options");
		optionsLabel->SetColor(sf::Color::Black);
		g->AddObject(optionsLabel);
		pageGuis.push_back(g);
	}
	//CONTROLS PAGE
	{
		GUI* g = new GUI();
		GUILabel* controlsLabel = new GUILabel(sf::Vector2f(0.5f, 0.13f), sf::Vector2f(0.9f, 0.025f), "Controls");
		controlsLabel->SetColor(sf::Color::Black);
		g->AddObject(controlsLabel);
		pageGuis.push_back(g);
		selectedBind = -1;
		bindCodes = {};
		bindGUIs = {};
		AddBind("Pause", &binds::Pause);
		AddBind("Fullscreen", &binds::Fullscreen);
	}
	currentGUI = 0;
}

void Settings::AddBind(std::string label, int* value)
{
	bindCodes.push_back(value);
	GUI* g = new GUI();
	float lowestPos = 0.3f;
	float gap = 0.1f;
	if (bindGUIs.size() > 0)
	{
		lowestPos = bindGUIs[bindGUIs.size() - 1]->GUIObjects[0]->position.y + gap;
	}
	GUILabel* l = new GUILabel(sf::Vector2f(0.3f, lowestPos), sf::Vector2f(0.2f, 0.03f), label);
	l->origin = sf::Vector2f(1.f, 0.5f);
	l->SetColor(sf::Color::Black);
	GUIPanel* p = new GUIPanel(sf::Vector2f(0.66f, lowestPos), sf::Vector2f(0.15f, 0.04f), sf::Color(100, 100, 100));
	p->blocksMouseInput = true;
	GUILabel* l2 = new GUILabel(sf::Vector2f(0.66f, lowestPos), sf::Vector2f(0.1f, 0.03f), binds::GetName(*value));
	l2->SetColor(sf::Color::Black);
	g->AddObject(l);
	g->AddObject(p);
	g->AddObject(l2);
	bindGUIs.push_back(g);
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
			framerate = round(s1->pValue);
			l1->value = "Framerate: " + std::to_string(framerate) + " fps";
			window->setVerticalSyncEnabled(false);
			window->setFramerateLimit(framerate);
		}
		GUISlider* s2 = dynamic_cast<GUISlider*>(cGUI->GUIObjects[5]);
		GUILabel* l2 = dynamic_cast<GUILabel*>(cGUI->GUIObjects[4]);
		if (s2->value > 0.99f)
		{
			saveInterval = -1;
			l2->value = "Autosave Interval: Never";
		}
		else
		{
			saveInterval = s2->pValue;
			l2->value = "Autosave Interval: " + std::to_string(saveInterval) + " minutes";
		}
		if (cGUI->GUIObjects[0]->isClicked())
		{
			currentGUI = 1;
		}
	}
	else if (currentGUI == 1)
	{

		for (uint i = 0; i < bindGUIs.size(); i++)
		{
			if (abs(InputHandler::scroll.y) > 0.05f)
			{
				for (uint j = 0; j < bindGUIs[i]->GUIObjects.size(); j++)
				{
					float rate = 0.03f;
					bindGUIs[i]->GUIObjects[j]->position += sf::Vector2f(0.f, InputHandler::scroll.y * rate);
				}
			}
			bindGUIs[i]->Update(dt);
			if (selectedBind == -1)
			{
				if (bindGUIs[i]->GUIObjects[1]->isClicked())
				{
					selectedBind = i;
					InputHandler::RemoveMbPressed(sf::Mouse::Button::Left);
					dynamic_cast<GUILabel*>(bindGUIs[i]->GUIObjects[2])->value = "...";
				}
			}
		}
		if (selectedBind != -1)
		{
			if (InputHandler::keysPressed.size() > 0)
			{
				int code = binds::keyToCode(InputHandler::keysPressed[0]);
				*bindCodes[selectedBind] = code;
				std::cout << std::to_string(binds::Pause) << std::endl;
				dynamic_cast<GUILabel*>(bindGUIs[selectedBind]->GUIObjects[2])->value = binds::GetName(code);
				selectedBind = -1;
				InputHandler::RemoveKeyPressed(InputHandler::keysPressed[0]);
			}
			else if (InputHandler::mouseButtonsPressed.size() > 0)
			{
				int code = binds::buttonToCode(InputHandler::mouseButtonsPressed[0]);
				*bindCodes[selectedBind] = code;
				std::cout << std::to_string(binds::Pause) << std::endl;
				dynamic_cast<GUILabel*>(bindGUIs[selectedBind]->GUIObjects[2])->value = binds::GetName(code);
				selectedBind = -1;
				InputHandler::RemoveMbPressed(InputHandler::mouseButtonsPressed[0]);
			}
		}
	}
}

void Settings::Render()
{
	behindGUI->Render();
	bgGUI->Render();
	pageGuis[currentGUI]->Render();
	if (currentGUI == 1)
	{
		for (uint i = 0; i < bindGUIs.size(); i++)
		{
			bindGUIs[i]->Render();
		}
	}
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
