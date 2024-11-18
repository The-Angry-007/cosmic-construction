#include "GUI.hpp"
#include "InputHandler.hpp"

GUI::GUI()
{
	GUIObjects = {};
}

void GUI::AddObject(GUIObject* object)
{
	GUIObjects.push_back(object);
}
void GUI::InsertObject(GUIObject* object, int index)
{
	GUIObjects.insert(GUIObjects.begin() + index, object);
}

//basic linear search algorithm
int GUI::GetIndex(GUIObject* object)
{
	for (uint i = 0; i < GUIObjects.size(); i++)
	{
		if (GUIObjects[i] == object)
		{
			return i;
		}
	}
	return -1;
}
void GUI::RemoveObject(int index)
{
	delete GUIObjects[index];
	GUIObjects.erase(GUIObjects.begin() + index);
}
GUI::~GUI()
{
	for (uint i = 0; i < GUIObjects.size(); i++)
	{
		delete GUIObjects[i];
	}
}

void GUI::Update(float dt)
{
	for (uint i = 0; i < GUIObjects.size(); i++)
	{
		GUIObjects[i]->Update(dt);
	}
}

void GUI::Render()
{
	for (uint i = 0; i < GUIObjects.size(); i++)
	{
		GUIObjects[i]->Render();
	}
}

void GUI::RenderToTexture(sf::RenderTexture* text)
{
	for (uint i = 0; i < GUIObjects.size(); i++)
	{
		GUIObjects[i]->RenderToTexture(text);
	}
}