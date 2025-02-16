#include "Hitbox.hpp"

Hitbox::Hitbox(sf::Vector2f position, sf::Vector2f size)
{
	this->position = position;
	this->size = size;
	currentPos = position;
	currentSize = size;
	shapes = {};
}

Hitbox::~Hitbox()
{
	for (uint i = 0; i < shapes.size(); i++)
	{
		delete shapes[i];
	}
}

void Hitbox::AddShape(HitboxShape* shape)
{
	shape->SetTransform(currentPos, currentSize);
	shapes.push_back(shape);
}
void Hitbox::SetTransform(sf::Vector2f position, sf::Vector2f size)
{
	currentPos = this->position + position;
	currentSize = sf::Vector2f(size.x * this->size.x, size.y * this->size.y);
	for (uint i = 0; i < shapes.size(); i++)
	{
		shapes[i]->SetTransform(currentPos, currentSize);
	}
}
void Hitbox::ResetTransform()
{
	currentPos = position;
	currentSize = size;
}
//2 hitboxes intersect if any shape in the first one intersects any shape in the second one.
bool Hitbox::intersects(Hitbox* other)
{
	for (uint i = 0; i < shapes.size(); i++)
	{
		for (uint j = 0; j < other->shapes.size(); j++)
		{
			if (shapes[i]->intersects(other->shapes[j]))
			{
				return true;
			}
		}
	}
	return false;
}

void Hitbox::Display(std::vector<Hitbox*> hitboxes)
{
	//must find whether this hitbox collides with any others
	bool colliding = false;
	for (uint i = 0; i < hitboxes.size(); i++)
	{
		if (hitboxes[i] == this)
		{
			continue;
		}
		if (intersects(hitboxes[i]))
		{
			colliding = true;
			break;
		}
	}
	//then display each shape
	for (uint i = 0; i < shapes.size(); i++)
	{
		shapes[i]->Display(colliding);
	}
}

bool Hitbox::intersectsPoint(sf::Vector2f point)
{
	for (uint i = 0; i < shapes.size(); i++)
	{
		if (shapes[i]->intersectsPoint(point))
		{
			return true;
		}
	}
	return false;
}