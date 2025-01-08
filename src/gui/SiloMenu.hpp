#pragma once
#include "GUIItem.hpp"
#include "game/StorageSilo.hpp"
#include "gui.hpp"
class StorageSilo;
class SiloMenu : public GUI
{
public:
	StorageSilo* silo;
	SiloMenu(StorageSilo* s);
	std::vector<GUIItem> items;
	void Update(float dt);
	void Render();
};