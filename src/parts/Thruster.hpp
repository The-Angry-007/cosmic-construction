#pragma once
#include "parts/Part.hpp"

class Thruster : public Part
{
public:
	Thruster(int index, b2Vec2 pos, float angle);
	sf::Texture* ignitedTexture;
	sf::Sprite* ignitedSprite;
	sf::Texture* coneTexture;
	sf::Sprite* coneSprite;
	sf::Texture* activeTexture;
	float coneAngle;
	bool active;
	void Update(double dt);
	void Render();
	void InitSprites();
	Thruster(std::string saveString);
	std::string toString();
};