#include "GUICheckbox.hpp"

GUICheckbox::GUICheckbox(sf::Vector2f position, sf::Vector2f size, sf::Color col)
{
	this->position = position;
	this->size = size;
	checked = false;
	checkImage = new GUIImage(position, size, "resources/images/tick.png");
	bgObj = new GUIPanel(position, size, col);
	bgObj->keepAspectRatio = true;
	bgObj->ratio = 1.f;
	checkImage->keepAspectRatio = true;
	blocksMouseInput = true;
	hitbox = new Hitbox(sf::Vector2f(0.f, 0.f), sf::Vector2f(1.f, 1.f));
	hitbox->AddShape(new HitboxRect(position, size));
}

void GUICheckbox::Update(float dt)
{
	checkImage->Update(dt);
	bgObj->Update(dt);
	if (isClicked())
	{
		checked = !checked;
	}
}
void GUICheckbox::Render()
{
	bgObj->Render();
	if (checked)
	{
		checkImage->Render();
	}
}