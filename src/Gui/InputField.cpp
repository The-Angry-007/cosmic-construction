#include "Include.hpp"
InputField::InputField(sf::FloatRect bounds, sf::Color col, int maxChars)
{
	this->bounds = bounds;
	this->bgCol = col;
	this->maxChars = maxChars;
	selectButton = new Button(
		sf::Vector2f(bounds.left + bounds.width / 2.f, bounds.top + bounds.height / 2.f),
		sf::Vector2f(bounds.width, bounds.height),
		col,
		"");
	label = new Label("", bounds, sf::Color::Black);
	text = "";
	selected = false;
	typeSpot = 0;
}
InputField::InputField(sf::Vector2f pos, sf::Vector2f size, sf::Color col, int maxChars)
{
	sf::Vector2f hs = size / 2.f;
	sf::FloatRect bounds(pos.x - hs.x, pos.y - hs.y, size.x, size.y);
	this->bounds = bounds;
	this->bgCol = col;
	this->maxChars = maxChars;
	selectButton = new Button(
		sf::Vector2f(bounds.left + bounds.width / 2.f, bounds.top + bounds.height / 2.f),
		sf::Vector2f(bounds.width, bounds.height),
		col,
		"");
	label = new Label("", bounds, sf::Color::Black);
	text = "";
	selected = false;
}
void InputField::Update()
{
	if (selected && (inp.mbDown(sf::Mouse::Button::Left) || inp.mbDown(sf::Mouse::Button::Right) || inp.keyPressed(sf::Keyboard::Key::Enter)))
	{
		selected = false;
		label->SetText(text);
	}
	{
	}
	if (selectButton->clicked())
	{
		selected = true;
		typeSpot = text.size();
		inp.RemoveMouseButtonPressed(sf::Mouse::Button::Left);
		inp.RemoveMouseButtonDown(sf::Mouse::Button::Left);
	}
	if (selected)
	{

		menu.getOpenGui()->mouseBlockedByGui = true;
		if (inp.keyPressed(sf::Keyboard::Key::Right) && typeSpot < (int)text.size())
			typeSpot++;
		if (inp.keyPressed(sf::Keyboard::Key::Left) && typeSpot > 0)
			typeSpot--;
		if (inp.typedText == "\b")
		{
			if (typeSpot > 0)
			{
				text.erase(text.begin() + typeSpot - 1);
				typeSpot--;
			}
		}
		else if ((maxChars == -1 || text.size() < (uint)maxChars))
		{
			for (uint i = 0; i < inp.typedText.size(); i++)
			{
				text.insert(text.begin() + typeSpot + i, inp.typedText[i]);
			}
			typeSpot += inp.typedText.size();
		}
		std::string withTyping = text;

		withTyping = "";
		for (int i = 0; i < typeSpot; i++)
		{
			withTyping += text[i];
		}
		withTyping += "|";
		for (int i = typeSpot; i < (int)text.size(); i++)
		{
			withTyping += text[i];
		}
		label->SetText(withTyping);
	}
}
void InputField::Render()
{
	selectButton->Render();
	label->Render();
}