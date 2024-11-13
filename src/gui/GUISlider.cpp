#include "GUISlider.hpp"
#include "utils.hpp"

GUISlider::GUISlider(sf::Vector2f position, sf::Vector2f size, GUIObject* knob, GUIObject* background, GUIObject* completion)
{
	this->position = position;
	this->size = size;
	this->knob = knob;
	this->background = background;
	this->completion = completion;
	value = 0.5f;
	knob->position = this->position;
	background->position = this->position;
	background->size = this->size;
	if (completion != nullptr)
	{
		completion->position = Lerp(position - sf::Vector2f(size.x, 0), position, 0.5f);
		completion->size = sf::Vector2f(size.x * value, size.y);
	}
}

void GUISlider::Update(float dt)
{}
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