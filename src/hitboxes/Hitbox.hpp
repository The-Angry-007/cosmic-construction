#pragma once
#include "HitboxShape.hpp"
class Hitbox
{
public:
	std::vector<HitboxShape*> shapes;
	sf::Vector2f position;
	sf::Vector2f size;
	sf::Vector2f currentPos;
	sf::Vector2f currentSize;

	Hitbox(sf::Vector2f position, sf::Vector2f size);
	~Hitbox();
	void AddShape(HitboxShape* shape);
	void SetTransform(sf::Vector2f position, sf::Vector2f size);
	void ResetTransform();
	bool intersects(Hitbox* other);

	//temporary function for debugging
	void Display(std::vector<Hitbox*> hitboxes);
};
