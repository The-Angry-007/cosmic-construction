#pragma once
#include "box2d/box2d.h"
extern void drawLine(sf::Vector2f point1, sf::Vector2f point2, float thickness, sf::Color col);

extern void GetMaxFontSize(sf::Text* text, sf::Vector2f bounds);

extern float Lerp(float a, float b, float c);

extern std::vector<std::string> split(std::string str, char splitter);

bool mouseTouchingBody(b2Body* body);