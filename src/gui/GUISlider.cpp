#include "GUISlider.hpp"
#include "InputHandler.hpp"
#include "utils.hpp"
GUISlider::GUISlider(sf::Vector2f position, sf::Vector2f size, GUIObject* knob, GUIObject* background, GUIObject* completion)
{
	this->position = position;
	this->size = size;
	this->knob = knob;
	knob->blocksMouseInput = true;
	this->background = background;
	this->completion = completion;
	value = 0.5f;
	knob->position = this->position;
	background->position = this->position;
	background->size = this->size;
	selected = false;
	AdjustFromVal();
}

void GUISlider::AdjustFromVal()
{
	knob->position = Lerp(position - sf::Vector2f(size.x, 0), position + sf::Vector2f(size.x, 0), value);

	if (completion != nullptr)
	{
		completion->position = Lerp(position - sf::Vector2f(size.x, 0), knob->position, 0.5f);
		completion->size = sf::Vector2f(size.x * value, size.y);
	}
}

void GUISlider::Update(float dt)
{
	if (selected)
	{
		float x = InputHandler::guiMP.x;
		if (x < position.x - size.x)
		{
			x = position.x - size.x;
		}
		else if (x > position.x + size.x)
		{
			x = position.x + size.x;
		}
		value = x / (2 * size.x);
		if (InputHandler::mbReleased(sf::Mouse::Button::Left))
		{
			selected = false;
		}
	}
	else
	{
		if (knob->isClicked())
		{
			selected = true;
		}
	}
	AdjustFromVal();
}
void GUISlider::Render()
{
	background->Render();
	if (completion != nullptr)
	{
		completion->Render();
	}
	knob->Render();
}

GUISlider::~GUISlider()
{
	delete knob;
	delete background;
	if (completion != nullptr)
	{
		delete completion;
	}
}