#include "GUIItem.hpp"
#include "Main.hpp"
#include "game/ResourceHandler.hpp"
GUIItem::GUIItem(sf::Vector2f position, sf::Vector2f size, int typeID, int amount)
{
	this->position = position;
	this->size = size;
	this->typeID = typeID;
	this->amount = amount;
	image = new GUIImage(position, size, "");
	if (amount != 0)
	{
		label = new GUILabel(position + size / 2.f, size / 4.f, std::to_string(amount));
		label->origin = sf::Vector2f(1.f, 1.f);
	}
	else
		label = nullptr;

	ResourceHandler::itemAtlas->SetSprite(image->sprite, typeID);
	image->keepAspectRatio = true;
	image->origin = sf::Vector2f(0.5f, 0.5f);
	image->blocksMouseInput = true;
}
bool GUIItem::isClicked()
{
	return image->isClicked();
}
void GUIItem::Update(float dt)
{
}
void GUIItem::RenderToTexture(sf::RenderTexture* texture)
{
	image->position = position;
	image->size = size;
	image->RenderToTexture(texture);
	actualSize = sf::Vector2f(image->sprite.getGlobalBounds().width / width / 2.f, image->sprite.getGlobalBounds().height / height / 2.f);
	if (label != nullptr)
	{
		label->position = position + actualSize / 2.f;
		label->size = actualSize / 4.f;
		label->RenderToTexture(texture);
	}
}
void GUIItem::Render()
{
	image->position = position;
	image->size = size;
	image->Render();
	actualSize = sf::Vector2f(image->sprite.getGlobalBounds().width / width / 2.f, image->sprite.getGlobalBounds().height / height / 2.f);
	if (label != nullptr)
	{
		label->position = position + actualSize / 2.f;
		label->size = actualSize / 4.f;
		label->Render();
	}
}

void GUIItem::SetAmount(int amount)
{
	this->amount = amount;
	if (amount != 0)
	{
		label->value = std::to_string(amount);
	}
}