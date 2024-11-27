#include "GUI.hpp"
#include "InputHandler.hpp"
//constructor: only thing to do is initialise guiobjects array.
GUI::GUI()
{
	GUIObjects = {};
}
//just takes a pointer to a guiobject and adds it to the array of objects.
void GUI::AddObject(GUIObject* object)
{
	GUIObjects.push_back(object);
}
//inserts an object so that its position is the index specified.
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
	//not in list
	return -1;
}
//removes the object at the given index.
void GUI::RemoveObject(int index)
{
	//need to call delete since it is a pointer.
	delete GUIObjects[index];
	GUIObjects.erase(GUIObjects.begin() + index);
}
//destructor just deletes every gui object
GUI::~GUI()
{
	for (uint i = 0; i < GUIObjects.size(); i++)
	{
		delete GUIObjects[i];
	}
}
//update just updates all gui objects
void GUI::Update(float dt)
{
	for (uint i = 0; i < GUIObjects.size(); i++)
	{
		GUIObjects[i]->Update(dt);
	}
}
//render just renders all gui objects
void GUI::Render()
{
	for (uint i = 0; i < GUIObjects.size(); i++)
	{
		GUIObjects[i]->Render();
	}
}
//same as render but with a render texture instead of the window
void GUI::RenderToTexture(sf::RenderTexture* text)
{
	for (uint i = 0; i < GUIObjects.size(); i++)
	{
		GUIObjects[i]->RenderToTexture(text);
	}
}