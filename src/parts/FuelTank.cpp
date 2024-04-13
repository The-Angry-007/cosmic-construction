#include "parts/FuelTank.hpp"
#include "Main.hpp"
#include "utils.hpp"
FuelTank::FuelTank(int index, b2Vec2 pos, float angle)
{
	defaultRotation = angle;
	this->index = index;
	SetCapacity();
	texture = new sf::Texture();
	std::string path = "resources/textures/fuelTank" + std::to_string(index) + ".png";
	if (!texture->loadFromFile(path))
	{
		window->close();
	}
	sprite = new sf::Sprite(*texture);
	sf::Vector2u size = texture->getSize();
	sprite->setScale(4.f, 4.f);
	sprite->setOrigin(size.x / 2, size.y / 2);
	//box2d setup
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position = pos;
	bodyDef.angle = angle;
	body = game->world->CreateBody(&bodyDef);
	b2PolygonShape shape;
	shape.SetAsBox(1.f, 0.5f);
	body->CreateFixture(&shape, capacity + 100.f);
}
void FuelTank::Update(double dt)
{
	UpdateDensity();
}
void FuelTank::Render()
{
	b2Vec2 bpos = body->GetPosition();
	sprite->setPosition(bpos.x * 128, -bpos.y * 128);
	sprite->setRotation(-body->GetAngle() / 3.14159f * 180.f);
	window->draw(*sprite);
}
void FuelTank::UpdateDensity()
{
	body->GetFixtureList()->SetDensity(capacity + 100.f);
}
void FuelTank::SetCapacity()
{
	switch (index)
	{
		case 0:
			//this is the number of litres in a cylinder height 0.5m radius 0.5m
			capacity = 785.f;
			maxCapacity = 785.f;
	}
}
std::string FuelTank::toString()
{
	std::string str = "1 ";
	str += std::to_string(index) + " ";
	str += std::to_string(body->GetPosition().x) + " " + std::to_string(body->GetPosition().y);
	str += " " + std::to_string(body->GetAngle());
	str += " " + std::to_string(body->GetLinearVelocity().x) + " " + std::to_string(body->GetLinearVelocity().y);
	str += " " + std::to_string(body->GetAngularVelocity());
	str += " " + std::to_string(defaultRotation);
	str += " " + std::to_string(capacity);
	return str;
}

FuelTank::FuelTank(std::string saveString)
{
	std::vector<std::string> parts = split(saveString, ' ');
	index = std::stoi(parts[0]);
	SetCapacity();
	capacity = std::stof(parts[8]);
	texture = new sf::Texture();
	std::string path = "resources/textures/fuelTank" + std::to_string(index) + ".png";
	if (!texture->loadFromFile(path))
	{
		window->close();
	}
	sprite = new sf::Sprite(*texture);
	sf::Vector2u size = texture->getSize();
	sprite->setScale(4.f, 4.f);
	sprite->setOrigin(size.x / 2, size.y / 2);
	//box2d setup
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position = b2Vec2(std::stof(parts[1]), std::stof(parts[2]));
	bodyDef.angle = std::stof(parts[3]);
	bodyDef.linearVelocity = b2Vec2(std::stof(parts[4]), std::stof(parts[5]));
	bodyDef.angularVelocity = std::stof(parts[6]);
	defaultRotation = std::stof(parts[7]);
	body = game->world->CreateBody(&bodyDef);
	b2PolygonShape shape;
	shape.SetAsBox(1.f, 0.5f);

	body->CreateFixture(&shape, 7850.f);
}