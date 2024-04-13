#include "Include.hpp"
Slider::Slider(sf::Vector2f pos, sf::Vector2f size, sf::Color bgCol, sf::Color filledCol, sf::Color knobCol)
{
	this->pos = pos;
	this->size = size;
	//clockwise from upwards
	bgRect = new sf::RectangleShape();
	bgRect->setFillColor(bgCol);
	knob = new sf::RectangleShape();
	knob->setFillColor(knobCol);
	filledRect = new sf::RectangleShape();
	filledRect->setFillColor(filledCol);
	value = 0.f;
	selected = false;
	updateFunction = defaultUpdateFunc;
}
void Slider::Update()
{
	// std::cout << value << std::endl;
	if (inp.mbPressed(sf::Mouse::Button::Left))
	{
		sf::Vector2f dif = sf::Vector2f(inp.mousePos.x / (float)width, inp.mousePos.y / (float)height) - pos;
		if (dif.x > -size.x / 2.f && dif.x < size.x / 2.f && dif.y > -size.y && dif.y < 0)
		{
			selected = true;
			inp.RemoveMouseButtonDown(sf::Mouse::Button::Left);
			inp.RemoveMouseButtonPressed(sf::Mouse::Button::Left);
		}
	}
	if (selected)
	{
		float rel = (inp.mousePos.y / (float)height) - pos.y;
		value = -rel / size.y;
		if (value < 0.f)
		{
			value = 0.f;
		}
		if (value > 1.f)
		{
			value = 1.f;
		}
		if (inp.mbReleased(sf::Mouse::Button::Left))
		{
			selected = false;
		}
	}
	updateFunction(value);
}

void Slider::Render()
{
	sf::Vector2f sPos(pos.x * width, pos.y * height);
	sf::Vector2f sSize(size.x * width, size.y * height);
	bgRect->setPosition(sPos);
	bgRect->setSize(sSize);
	bgRect->setOrigin(sSize.x / 2.f, sSize.y);
	window->draw(*bgRect);
	filledRect->setPosition(sPos);
	filledRect->setSize(sf::Vector2f(sSize.x, sSize.y * -value));
	filledRect->setOrigin(sSize.x / 2.f, 0.f);
	window->draw(*filledRect);
	knob->setSize(sf::Vector2f(sSize.x * 1.001f, sSize.x * 1.1001f));

	knob->setPosition(sPos.x, sPos.y + Lerp(-knob->getSize().y / 2.f, -sSize.y + knob->getSize().y / 2.f, value));
	knob->setOrigin(knob->getSize().x / 2.f, knob->getSize().y / 2.f);
	window->draw(*knob);
}

void defaultUpdateFunc(float val)
{}