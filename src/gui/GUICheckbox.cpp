#include "GUICheckbox.hpp"
//constructor for the checkbox - takes a position, size and colour for the background
GUICheckbox::GUICheckbox(sf::Vector2f position, sf::Vector2f size, sf::Color col)
{
	this->position = position;
	this->size = size;
	//set to not checked by default
	checked = false;
	//create an image from the tick image
	checkImage = new GUIImage(position, size, "content/resources/images/tick.png");
	//create background image
	bgObj = new GUIPanel(position, size, col);
	//make sure the checkbox is always square
	bgObj->keepAspectRatio = true;
	bgObj->ratio = 1.f;
	checkImage->keepAspectRatio = true;
	//should be clickable
	blocksMouseInput = true;
	//copy hitbox of image
	hitbox = checkImage->hitbox;
}

void GUICheckbox::Update(float dt)
{
	//update image and background
	checkImage->Update(dt);
	bgObj->Update(dt);
	if (isClicked())
	{
		if (checked)
		{
			//exclusives is a list of checkboxes that should be mutually exclusive with this one.
			//if there are exclusives, then dont toggle the check when it is already checked.
			if (exclusives.size() > 0)
			{
				return;
			}
			//otherwise, do toggle it.
			else
			{
				checked = false;
			}
		}
		//if its not checked:
		else
		{
			//if it has exclusives, make sure they become unchecked
			for (uint i = 0; i < exclusives.size(); i++)
			{
				exclusives[i]->checked = false;
			}
			//then make this checkbox checked
			checked = true;
		}
	}
}
void GUICheckbox::Render()
{
	//if it is checked, draw the background then the image.
	//otherwise, draw the background on top of the image. this is because
	//the render function is required to scale the image, which keeps the hitbox accurate.
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