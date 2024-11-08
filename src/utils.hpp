#pragma once

extern bool RectIntersectsRect(sf::FloatRect rect1, sf::FloatRect rect2);

extern bool RectIntersectsCircle(sf::Vector2f pos, float r, sf::FloatRect rect);

extern bool CircleIntersectsCircle(sf::Vector2f pos1, float r1, sf::Vector2f pos2, float r2);

float clamp(float val, float min, float max);
