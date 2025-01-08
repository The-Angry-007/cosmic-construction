#include "GUIItem.hpp"
#include "Main.hpp"
#include "game/ResourceHandler.hpp"
GUIItem::GUIItem(sf::Vector2f position, sf::Vector2f size, int typeID, int amount)
{
	this->position = position;
	this->size = size;
	this->typeID = typeID;
	this->amount = amount;
	image = new GUIImage(position, size, "resources/images/squareButton.png");
	label = new GUILabel(position + size / 2.f, size / 4.f, std::to_string(amount));
	label->origin = sf::Vector2f(1.f, 1.f);
	ResourceHandler::itemAtlas->SetSprite(image->sprite, typeID);
	image->keepAspectRatio = true;
}

void GUIItem::Update(float dt)
{
}
void GUIItem::RenderToTexture(sf::RenderTexture* texture)
{
	image->RenderToTexture(texture);
	actualSize = sf::Vector2f(image->sprite.getGlobalBounds().width / width / 2.f, image->sprite.getGlobalBounds().height / height / 2.f);
	label->position = position + actualSize / 2.f;
	label->size = actualSize / 4.f;
	label->RenderToTexture(texture);
}