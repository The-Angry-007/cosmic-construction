#include "LoadGame.hpp"
#include "InputHandler.hpp"
#include "Main.hpp"
#include "saving.hpp"
#include "utils.hpp"
LoadGame::LoadGame(GUIGalaxy* galaxy, GUIPanel* dimpanel)
{
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
	std::vector<std::string> dirs = SaveHandler::ListDirectories(SaveHandler::workingDir + "\\saves");
	sf::Vector2f startPos(0.5f, 0.3f);
	float gap = 0.24f;
	for (uint i = 0; i < dirs.size(); i++)
	{
		saveSlots.push_back(new GUISaveSlot(startPos, SaveHandler::workingDir + "\\saves\\" + dirs[i]));
		startPos.y += gap;
	}
}

void LoadGame::Update(float dt)
{
	float move = InputHandler::scroll.y * 0.05f;

	if (move < 0)
	{
		float lowest = saveSlots[saveSlots.size() - 1]->bgObj->position.y + saveSlots[0]->bgObj->size.y;
		if (lowest - move < 0.90f)
		{
			move = 0.f;
		}
	}
	else if (move > 0)
	{
		float highest = saveSlots[0]->bgObj->position.y - saveSlots[0]->bgObj->size.y;
		if (highest + move > 0.22f)
		{
			move = 0.f;
		}
	}
	for (uint i = 0; i < GUIObjects.size(); i++)
	{
		GUIObjects[i]->Update(dt);
	}
	for (uint i = 0; i < saveSlots.size(); i++)
	{
		saveSlots[i]->Move(move);
		saveSlots[i]->Update(dt);
		if (saveSlots[i]->deleteBG->isClicked())
		{
			Reload();
			return;
		}
		if (saveSlots[i]->bgObj->isClicked())
		{
			std::string saves = SaveHandler::workingDir + "\\saves\\";
			std::string folder = saveSlots[i]->path.substr(saves.length());
			std::cout << folder << std::endl;
			SaveHandler::LoadGame(std::stoi(folder));
			guihandler.OpenGUI(5);
		}
	}
}
void LoadGame::Render()
{

	for (uint i = 0; i < GUIObjects.size(); i++)
	{
		GUIObjects[i]->Render();
	}

	sf::RenderTexture t;
	t.create(width, height);
	t.clear(sf::Color::Transparent);
	t.setView(sf::View(sf::Vector2f(width / 2.f, height / 2.f), sf::Vector2f(width, height)));

	for (uint i = 0; i < saveSlots.size(); i++)
	{
		saveSlots[i]->RenderToTexture(&t);
	}
	t.display();
	sf::Sprite s;
	s.setPosition(0.1f * width, 0.18f * height);
	s.setTexture(t.getTexture());
	s.setTextureRect(sf::IntRect(sf::Vector2i(0.1f * width, 0.18f * height), sf::Vector2i(0.8f * width, 0.72f * height)));
	window->draw(s);
}

void LoadGame::Reload()
{
	for (uint i = 0; i < saveSlots.size(); i++)
	{
		delete saveSlots[i];
	}
	saveSlots = {};
	std::vector<std::string> dirs = SaveHandler::ListDirectories(SaveHandler::workingDir + "\\saves");
	std::vector<int> creationTimes = {};
	std::vector<std::string*> ptrs = {};
	for (uint i = 0; i < dirs.size(); i++)
	{
		ptrs.push_back(&dirs[i]);
		std::string path = SaveHandler::workingDir;
		path += "\\saves\\" + dirs[i];
		path += "\\metadata.txt";
		auto data = Split(SaveHandler::ReadData(path), '\n');
		creationTimes.push_back(std::stoi(data[2]));
	}
	//sort directories using bubble sort algorithm
	for (uint i = 0; i < dirs.size(); i++)
	{
		bool swapped = false;
		for (int j = 0; j < dirs.size() - i - 1; j++)
		{
			if (creationTimes[j] < creationTimes[j + 1])
			{
				int temp = creationTimes[j];
				creationTimes[j] = creationTimes[j + 1];
				creationTimes[j + 1] = temp;
				std::string* temp2 = ptrs[j];
				ptrs[j] = ptrs[j + 1];
				ptrs[j + 1] = temp2;
				swapped = true;
			}
		}
		if (!swapped)
		{
			break;
		}
	}
	sf::Vector2f startPos(0.5f, 0.3f);
	float gap = 0.24f;
	for (uint i = 0; i < dirs.size(); i++)
	{
		saveSlots.push_back(new GUISaveSlot(startPos, SaveHandler::workingDir + "\\saves\\" + *ptrs[i]));
		startPos.y += gap;
	}
}