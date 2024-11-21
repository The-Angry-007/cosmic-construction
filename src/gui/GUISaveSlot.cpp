#include "GUISaveSlot.hpp"
#include "../Main.hpp"
#include "../saving.hpp"
#include "../utils.hpp"
GUISaveSlot::GUISaveSlot(sf::Vector2f position, std::string path)
{
	this->position = position;
	auto slotData = Split(SaveHandler::ReadData(path + "\\metadata.txt"), '\n');
	size = sf::Vector2f(0.35f, 0.1f);
	bgObj = new GUIPanel(position, size, sf::Color(177, 177, 177));
	sf::Vector2f nameSize(0.3f, 0.07f);
	sf::Vector2f offset(0.01f, 0.01f);
	nameLabel = new GUILabel(position - size + nameSize * 0.5f + offset, nameSize * 0.5f, slotData[0]);
	nameLabel->SetColor(sf::Color::Black);
	nameLabel->text.setStyle(sf::Text::Bold);
	nameLabel->origin = sf::Vector2f(0.f, 0.f);
}

void GUISaveSlot::Update(float dt)
{
	bgObj->Update(dt);
	nameLabel->Update(dt);
	// playtimeLabel->Update(dt);
	// modifiedLabel->Update(dt);
	// deleteButton->Update(dt);
}

void GUISaveSlot::Move(float amt)
{
	this->position.y += amt;
	bgObj->position.y += amt;
	nameLabel->position.y += amt;
}

void GUISaveSlot::RenderToTexture(sf::RenderTexture* texture)
{
	//draw an outline (this is measured in pixels)
	float outlineSize = 1;
	sf::Vector2f adjustment(outlineSize / width, outlineSize / height);
	sf::Color original = bgObj->color;
	bgObj->SetColor(sf::Color::Black);
	bgObj->size += adjustment;
	bgObj->RenderToTexture(texture);
	bgObj->SetColor(original);
	bgObj->size -= adjustment;
	bgObj->RenderToTexture(texture);
	nameLabel->RenderToTexture(texture);
}
GUISaveSlot::~GUISaveSlot()
{
	delete bgObj;
	delete nameLabel;
}