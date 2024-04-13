#pragma once

class GuiObject
{
public:
	sf::Vector2f pos;
	sf::Vector2f size;
	sf::FloatRect bounds;
	bool blocksMouseInput;
	bool isBlockingMouse();
	void Update();
	void Render();
	void SetBounds();
	GuiObject();
	~GuiObject();
};