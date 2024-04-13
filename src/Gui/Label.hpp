#pragma once
class Label
{
public:
	Label(std::string text, sf::FloatRect bounds, sf::Color col);
	Label(std::string text, sf::Vector2f pos, sf::Vector2f size, sf::Color col);
	void Render();
	void SetText(std::string text);
	void SetCol(sf::Color col);
	~Label();
	void setOrigin(sf::Vector2f origin);
	sf::FloatRect bounds;
	sf::Vector2f padding;

private:
	sf::Color col;
	std::string text;
	sf::Text label;
	sf::Vector2f origin;
};