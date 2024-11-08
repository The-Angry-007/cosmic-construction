#include "Hitbox.hpp"

Hitbox::Hitbox(sf::Vector2f position, sf::Vector2f size)
{
	this->position = position;
	this->size = size;
	currentPos = position;
	currentSize = size;
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
}
void Hitbox::ResetTransform()
{
	currentPos = position;
	currentSize = size;
}
bool Hitbox::intersects(Hitbox other)
{
	for (uint i = 0; i < shapes.size(); i++)
	{
		for (uint j = 0; j < other.shapes.size(); j++)
		{
			if (shapes[i]->intersects(other.shapes[j]))
			{
				return true;
			}
		}
	}
	return false;
}

void Hitbox::Display(std::vector<Hitbox*> hitboxes)
{
	std::vector<HitboxShape*> allshapes;
	for (uint i = 0; i < hitboxes.size(); i++)
	{
		if (hitboxes[i] == this)
		{
			continue;
		}
		for (uint j = 0; j < hitboxes[i]->shapes.size(); i++)
		{
			allshapes.push_back(hitboxes[i]->shapes[j]);
		}
	}
	for (uint i = 0; i < shapes.size(); i++)
	{
		shapes[i]->Display(allshapes);
	}
}