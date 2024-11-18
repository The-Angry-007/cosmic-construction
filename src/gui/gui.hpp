#pragma once
#include "GUIObject.hpp"
class GUI
{
public:
	std::vector<GUIObject*> GUIObjects;

	virtual void Render();
	virtual void Update(float dt);
	void AddObject(GUIObject* object);
	void InsertObject(GUIObject* object, int index);
	int GetIndex(GUIObject* object);
	void RemoveObject(int index);
	void RenderToTexture(sf::RenderTexture* text);
	GUI();
	~GUI();
};