#pragma once
#include "GUIItem.hpp"
#include "game/StorageSilo.hpp"
#include "gui.hpp"
class SiloMenu : public GUI
{
public:
	SiloMenu(StorageSilo* silo);
	std::vector<GUIItem> items;
	void Update(float dt);
	void Render();
};