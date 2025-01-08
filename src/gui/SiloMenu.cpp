#include "SiloMenu.hpp"
#include "Main.hpp"
SiloMenu::SiloMenu(StorageSilo* s)
{
	this->silo = s;
	items.push_back(GUIItem(
		sf::Vector2f(0.5f, 0.5f),
		sf::Vector2f(0.3f, 0.3f),
		0,
		1));
}

void SiloMenu::Update(float dt)
{
	for (int i = 0; i < items.size(); i++)
	{
		items[i].Update(dt);
	}
}
void SiloMenu::Render()
{
	sf::RenderTexture text;
	text.create(width, height);
	text.setView(sf::View(sf::Vector2f(width / 2.f, height / 2.f), sf::Vector2f(width, height)));
	text.clear(sf::Color::Transparent);
	for (int i = 0; i < items.size(); i++)
	{
		items[i].RenderToTexture(&text);
	}
	std::cout << "rendering menu" << std::endl;
	text.display();
	sf::Sprite s(text.getTexture());
	sf::IntRect bounds(sf::Vector2i(width * 0.1f, height * 0.16f), sf::Vector2i(width * 0.8f, height * (0.8f - 0.06f)));
	s.setTextureRect(bounds);
	s.setPosition(bounds.left, bounds.top);
	s.setOrigin(0.f, 0.f);

	window->draw(s);
}