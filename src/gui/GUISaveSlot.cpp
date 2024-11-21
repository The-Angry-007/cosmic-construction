#include "GUISaveSlot.hpp"

GUISaveSlot::GUISaveSlot(sf::Vector2f position, std::string path)
{
	this->position = position;
	size = sf::Vector2f(0.5f, 0.3f);
	bgObj = new GUIPanel(position, size, sf::Color(177, 177, 177));
	sf::Vector2f nameSize(0.3f, 0.1f);
	nameLabel = new GUILabel(position - size + nameSize * 0.5f, nameSize * 0.5f, "Name");
	nameLabel->SetColor(sf::Color::Black);
	nameLabel->text.setStyle(sf::Text::Bold);
}

void GUISaveSlot::Update(float dt)
{
	bgObj->Update(dt);
	nameLabel->Update(dt);
	playtimeLabel->Update(dt);
	modifiedLabel->Update(dt);
	deleteButton->Update(dt);
}

void GUISaveSlot::Move(float amt)
{
	this->position.y += amt;
	bgObj->position.y += amt;
	nameLabel->position.y += amt;
}

void GUISaveSlot::RenderToTexture(sf::RenderTexture* texture)
{
	bgObj->RenderToTexture(texture);
	nameLabel->RenderToTexture(texture);
}
GUISaveSlot::~GUISaveSlot()
{
	delete bgObj;
	delete nameLabel;
}