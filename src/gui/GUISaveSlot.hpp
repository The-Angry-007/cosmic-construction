#pragma once
#include "GUIButton.hpp"
#include "GUILabel.hpp"
#include "GUIObject.hpp"
#include "GUIPanel.hpp"
class GUISaveSlot : public GUIObject
{
public:
	GUIPanel* bgObj;
	GUILabel* nameLabel;
	GUILabel* playtimeLabel;
	GUILabel* modifiedLabel;
	GUIButton* deleteButton;
	std::string path;
	GUISaveSlot(sf::Vector2f position, std::string path);
	void Update(float dt);
	void Move(float amt);
	void RenderToTexture(sf::RenderTexture* texture);
	~GUISaveSlot();
};