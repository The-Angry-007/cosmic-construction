#include "GUIStructure.hpp"
#include "Main.hpp"
#include "game/ResourceHandler.hpp"
GUIStructure::GUIStructure(sf::Vector2f position, sf::Vector2f size, int typeID, std::vector<int> frames)
{
	this->position = position;
	this->size = size;
	this->typeID = typeID;
	images = {};
	for (int i = 0; i < frames.size(); i++)
	{
		GUIImage* im = new GUIImage(position, size, "");
		im->keepAspectRatio = true;
		im->blocksMouseInput = true;
		ResourceHandler::structureAtlas->SetSprite(im->sprite, typeID, frames[i]);
		images.push_back(im);
	}
}
void GUIStructure::Update(float dt)
{
	for (int i = 0; i < images.size(); i++)
	{
		images[i]->Update(dt);
	}
}
void GUIStructure::Render()
{
	actualSize = sf::Vector2f(0.f, 0.f);
	for (int i = 0; i < images.size(); i++)
	{
		images[i]->Render();
		sf::Vector2f s(images[i]->sprite.getGlobalBounds().width / width, images[i]->sprite.getGlobalBounds().height / height);
		if (s.x > actualSize.x)
		{
			actualSize.x = s.x;
		}
		if (s.y > actualSize.y)
		{
			actualSize.y = s.y;
		}
	}
}