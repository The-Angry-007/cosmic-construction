#pragma once
#include "GUIObject.hpp"
class GUI
{
public:
	std::vector<GUIObject*> GUIObjects;

	void Render();
	void Update(float dt);
	void AddObject(GUIObject* object);
	void InsertObject(GUIObject* object, int index);
	int GetIndex(GUIObject* object);
	void RemoveObject(int index);
	GUI();
	~GUI();
};