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
	hitbox = checkImage->hitbox;
}

void GUICheckbox::Update(float dt)
{
	checkImage->Update(dt);
	bgObj->Update(dt);
	if (isClicked())
	{
		if (checked)
		{
			if (exclusives.size() > 0)
			{
				return;
			}
			else
			{
				checked = false;
			}
		}
		else
		{
			for (uint i = 0; i < exclusives.size(); i++)
			{
				exclusives[i]->checked = false;
			}
			checked = true;
		}
	}
}
void GUICheckbox::Render()
{
	if (checked)
	{
		bgObj->Render();
		checkImage->Render();
	}
	else
	{
		checkImage->Render();
		bgObj->Render();
	}
}