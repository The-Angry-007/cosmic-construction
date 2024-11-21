#include "GUISaveSlot.hpp"
#include "../Main.hpp"
#include "../saving.hpp"
#include "../utils.hpp"
#include <ctime>
#include <iomanip>
#include <iostream>
GUISaveSlot::GUISaveSlot(sf::Vector2f position, std::string path)
{
	this->path = path;
	this->position = position;
	auto slotData = Split(SaveHandler::ReadData(path + "\\metadata.txt"), '\n');
	std::string playedString = "";
	std::string suffix = "seconds";
	float timePlayed = std::stof(slotData[1]);
	if (timePlayed > 60)
	{
		timePlayed /= 60;
		suffix = "minutes";
		if (timePlayed > 60)
		{
			timePlayed /= 60;
			suffix = "hours";
		}
	}
	//remove decimals
	std::stringstream stream;
	stream << std::fixed << std::setprecision(1) << timePlayed;
	playedString = stream.str();
	if (playedString.substr(playedString.length() - 2, 2) == ".0")
	{
		playedString = playedString.substr(0, playedString.length() - 2);
	}
	playedString = "Playtime: " + playedString + " " + suffix;
	size = sf::Vector2f(0.35f, 0.1f);
	bgObj = new GUIPanel(position, size, sf::Color(177, 177, 177));
	sf::Vector2f nameSize(0.5f, 0.06f);
	sf::Vector2f offset(0.01f, 0.01f);
	nameLabel = new GUILabel(position - size + nameSize * 0.5f + offset, nameSize * 0.5f, slotData[0]);
	nameLabel->SetColor(sf::Color::Black);
	nameLabel->text.setStyle(sf::Text::Bold);
	nameLabel->origin = sf::Vector2f(0.f, 0.f);
	sf::Vector2f playtimeSize(0.13f, 0.02f);
	playtimeLabel = new GUILabel(position + sf::Vector2f(size.x - playtimeSize.x, size.y - playtimeSize.y) - offset, playtimeSize, "");
	// playtimeLabel = new GUILabel(position + sf::Vector2f(size.x - offset.x, -size.x + offset.y * 2) - sf::Vector2f(playtimeSize.x, -playtimeSize.y), playtimeSize, "");
	playtimeLabel->value = playedString;
	playtimeLabel->origin = sf::Vector2f(1.f, 1.f);
	playtimeLabel->SetColor(sf::Color::Black);
	std::time_t time = std::stoi(slotData[2]);
	std::tm* localTime = std::localtime(&time);
	std::ostringstream oss;
	oss << std::put_time(localTime, "%d/%m/%Y");
	std::string modified = oss.str();
	modified = "Date Modified: " + modified;
	sf::Vector2f modifiedSize(0.2f, 0.02f);
	modifiedLabel = new GUILabel(position + sf::Vector2f(-size.x + modifiedSize.x, size.y - modifiedSize.y) + sf::Vector2f(offset.x, -offset.y), modifiedSize, modified);
	modifiedLabel->origin = sf::Vector2f(0.f, 1.f);
	modifiedLabel->SetColor(sf::Color::Black);
	bgObj->blocksMouseInput = true;
}

void GUISaveSlot::Update(float dt)
{
	bgObj->Update(dt);
	nameLabel->Update(dt);
	playtimeLabel->Update(dt);
	modifiedLabel->Update(dt);
	// deleteButton->Update(dt);
}

void GUISaveSlot::Move(float amt)
{
	this->position.y += amt;
	bgObj->position.y += amt;
	nameLabel->position.y += amt;
	playtimeLabel->position.y += amt;
	modifiedLabel->position.y += amt;
}

void GUISaveSlot::RenderToTexture(sf::RenderTexture* texture)
{
	//draw an outline (this is measured in pixels)
	float outlineSize = 2;
	sf::Vector2f adjustment(outlineSize / width, outlineSize / height);
	sf::Color original = bgObj->color;
	bgObj->SetColor(sf::Color(100, 100, 100));
	bgObj->size += adjustment;
	bgObj->RenderToTexture(texture);
	bgObj->SetColor(original);
	bgObj->size -= adjustment;
	bgObj->RenderToTexture(texture);
	nameLabel->RenderToTexture(texture);
	playtimeLabel->RenderToTexture(texture);
	modifiedLabel->RenderToTexture(texture);
}
GUISaveSlot::~GUISaveSlot()
{
	delete bgObj;
	delete nameLabel;
	delete playtimeLabel;
	delete modifiedLabel;
}