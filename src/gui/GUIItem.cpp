#include "GUIItem.hpp"

GUIItem::GUIItem(sf::Vector2f position, sf::Vector2f size, int typeID, int amount)
{
	this->position = position;
	this->size = size;
	this->typeID = typeID;
	this->amount = amount;
	this->image = new GUIImage(position, size, "resources/images/squareButton.png");
}

void GUIItem::Update(float dt)
{
}
void GUIItem::RenderToTexture(sf::RenderTexture* texture)
{
	this->image->RenderToTexture(texture);
}