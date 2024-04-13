#pragma once
class Slider
{
public:
	float value;
	sf::Vector2f pos; //pos of the start, origin is (0,0.5)
	sf::Vector2f size;
	sf::RectangleShape* bgRect;
	sf::RectangleShape* knob;
	sf::RectangleShape* filledRect;
	bool selected;
	Slider(sf::Vector2f pos, sf::Vector2f size, sf::Color bgCol = sf::Color(50, 50, 50), sf::Color filledCol = sf::Color(100, 100, 100), sf::Color knobCol = sf::Color(150, 150, 150));
	void Update();
	void Render();
	std::function<void(float val)> updateFunction;
};
void defaultUpdateFunc(float val);