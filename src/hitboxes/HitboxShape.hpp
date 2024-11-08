#pragma once
class HitboxShape
{
public:
	sf::Vector2f position;
	sf::Vector2f size;
	sf::Vector2f currentPos;
	sf::Vector2f currentSize;
	int index;

	~HitboxShape();
	HitboxShape();
	void SetTransform(sf::Vector2f position, sf::Vector2f size);
	void ResetTransform();
	virtual bool intersects(HitboxShape* other);
	virtual void Display(bool colliding);
};