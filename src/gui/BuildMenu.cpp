#include "BuildMenu.hpp"

BuildMenu::BuildMenu()
{
	// std::vector<std::string> titles;
	// for (int i = 0; i < 3; i++)
	// {
	// 	GUILabel* l = new GUILabel()
	// }
	bg = new GUIPanel(sf::Vector2f(0.5f, 0.5f), sf::Vector2f(0.4f, 0.4f), sf::Color(150, 150, 150));
}

void BuildMenu::Update(float dt)
{
	bg->Update(dt);
}
void BuildMenu::Render()
{
	bg->Render();
}