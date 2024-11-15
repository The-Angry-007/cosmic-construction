#include "GUIInputField.hpp"
#include "InputHandler.hpp"
GUIInputField::GUIInputField(sf::Vector2f position, sf::Vector2f size)
{
	this->position = position;
	this->size = size;
	label = new GUILabel(position, size, "");
	label->SetColor(sf::Color::Black);
	cursorPos = 0;
	changed = false;
	focused = false;
	value = "";
	hitbox = new Hitbox(sf::Vector2f(0.f, 0.f), sf::Vector2f(1.f, 1.f));
	hitbox->AddShape(new HitboxRect(position, size));
	blocksMouseInput = true;
}

void GUIInputField::Update(float dt)
{
	std::cout << cursorPos << std::endl;
	if (!focused)
	{
		displayValue = value;
		if (isClicked())
		{
			focused = true;
			cursorPos = value.length() - 1;
			if (!changed)
			{
				changed = true;
				value = "";
				cursorPos = -1;
			}
		}
	}
	else
	{
		std::string t = InputHandler::typedText;
		for (int i = 0; i < t.length(); i++)
		{
			if (t[i] != '\b')
			{
				value.insert(value.begin() + cursorPos + 1, t[i]);
				cursorPos++;
			}
			else
			{
				if (value.length() > 0)
				{
					value.erase(value.end() - 1);
					cursorPos--;
				}
			}
		}
		displayValue = "";
		for (int i = 0; i < value.length(); i++)
		{
			displayValue += value[i];
			if (i == cursorPos)
			{
				displayValue += '|';
			}
		}
		if (value.length() == 0)
		{
			displayValue += "|";
		}
		if (InputHandler::mbPressed(sf::Mouse::Button::Left) && !isClicked())
		{
			focused = false;
			displayValue = value;
		}
		if (InputHandler::keyPressed(sf::Keyboard::Left))
		{
			cursorPos--;
			if (cursorPos < -1)
			{
				cursorPos = -1;
			}
		}
		if (InputHandler::keyPressed(sf::Keyboard::Right))
		{
			cursorPos++;
			if (cursorPos > value.length() - 1)
			{
				cursorPos--;
			}
		}
	}
}
void GUIInputField::SetTextCol(sf::Color color)
{
	label->SetColor(color);
}

GUIInputField::~GUIInputField()
{
	delete label;
}
void GUIInputField::Render()
{
	label->value = displayValue;
	label->Render();
}