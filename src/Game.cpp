#include "Game.hpp"
#include "Main.hpp"
#include "SaveHandler.hpp"
#include "box2d/box2d.h"
#include "inputHandler.hpp"
Game::Game()
{
}
void Game::NewGame()
{
	float blockWidth = 1.0f;	// Width of each block
	float blockHeight = 1.0f;	// Height of each block
	float blockSpacing = 0.01f; // Small vertical spacing between blocks to prevent them from sticking

	for (int i = 0; i < 0; ++i)
	{
		b2BodyDef blockBodyDef;
		blockBodyDef.type = b2_dynamicBody;
		blockBodyDef.position.Set((rand() / (float)RAND_MAX) * 2.f - 1.f, i * (blockHeight + blockSpacing)); // Stack blocks

		b2Body* blockBody = world->CreateBody(&blockBodyDef);
		blocks.push_back(blockBody);
		b2PolygonShape blockShape;
		blockShape.SetAsBox(blockWidth / 2.0f, blockHeight / 2.0f); // Half width and half height

		b2FixtureDef blockFixtureDef;
		blockFixtureDef.shape = &blockShape;
		blockFixtureDef.density = 10.0f;   // Set density to make it dynamic
		blockFixtureDef.friction = 0.5f;   // Add some friction
		blockFixtureDef.restitution = 0.f; // Add a little bounce

		blockBody->CreateFixture(&blockFixtureDef);
	}
	Structure structure;
	structure.AddPart(new Thruster(0, b2Vec2(0.f, 10.f), 0.f));
	structure.AddPart(new FuelTank(0, b2Vec2(0.f, 12.f), b2_pi));
	structure.AddPart(new FuelTank(0, b2Vec2(0.f, 13.f), b2_pi));
	structure.AddConnection(0, 1);
	structure.AddConnection(1, 2);
	structure.focused = true;
	structures.push_back(structure);
}
void Game::Init(bool newGame)
{
	timeScale = 1.f;
	frozen = false;
	this->savePath = SaveHandler::workingDir;
	paused = false;
	b2Vec2 gravity(0.f, 0.f);
	world = new b2World(gravity);
	// Define the ground body
	b2BodyDef groundBodyDef;
	groundBodyDef.position.Set(0.0f, -10.0f); // Position it (assuming 0,0 is the center and y is up)

	// Call the world object to create the ground body
	groundBody = world->CreateBody(&groundBodyDef);

	// Define and add the ground shape
	b2PolygonShape groundBox;
	groundBox.SetAsBox(50.0f, 10.0f); // Set as a box of 50 units wide and 10 units tall

	// Create a fixture with the shape on the body
	groundBody->CreateFixture(&groundBox, 0.0f); // Density is 0.0f because it's static

	timePassed = new sf::Clock();
	thrusterThrottle = 0.f;
	if (newGame)
	{
		NewGame();
	}
	else
	{
		SaveHandler::LoadGame();
	}
}
void Game::Update(double dt)
{
	if (inp.keyPressed(sf::Keyboard::Key::Escape))
	{
		TogglePaused();
	}
	if (paused)
	{
		return;
	}
	if (inp.keyPressed(sf::Keyboard::Space))
	{
		frozen = !frozen;
		timeScale = 1.f;
		if (frozen)
		{
			timeScale = 0.f;
		}
	}
	//update box2d world
	world->Step(dt * timeScale, 6, 2);

	for (uint i = 0; i < structures.size(); i++)
	{
		structures[i].Update(dt * timeScale);
	}
}
void Game::TogglePaused()
{
	if (!paused)
	{
		paused = true;
		menu.OpenMenu(5);
	}
	else
	{
		paused = false;
		menu.OpenMenu(4);
	}
}
void Game::Render()
{
	box2dBodyToSFML(groundBody, sf::Color::White);
	for (int i = 0; i < blocks.size(); i++)
	{
		box2dBodyToSFML(blocks[i], sf::Color::Red);
	}
	for (uint i = 0; i < structures.size(); i++)
	{
		structures[i].Render();
	}
}
Game::~Game()
{
}

sf::RectangleShape box2dBodyToSFML(b2Body* body, const sf::Color& color)
{
	float SCALE = 128.f;
	// Assuming the body has a polygon shape fixture
	b2Fixture* fixture = body->GetFixtureList();
	if (!fixture)
		return sf::RectangleShape();

	b2PolygonShape* polygonShape = dynamic_cast<b2PolygonShape*>(fixture->GetShape());
	if (!polygonShape)
		return sf::RectangleShape();

	// Get the size of the Box2D "box" shape
	b2Vec2 size = polygonShape->m_vertices[2]; // Assuming the first vertex is at the bottom-left

	sf::RectangleShape rectangle;
	rectangle.setSize(sf::Vector2f(size.x * 2.0f * SCALE, size.y * 2.0f * SCALE)); // Box2D's size is half-width and half-height
	rectangle.setOrigin(size.x * SCALE, size.y * SCALE);						   // Set origin to center for proper rotation
	rectangle.setPosition(SCALE * body->GetPosition().x, -SCALE * body->GetPosition().y);
	rectangle.setRotation(-body->GetAngle() * 180.0f / b2_pi); // Convert radians to degrees
	rectangle.setFillColor(color);
	window->draw(rectangle);
	return rectangle;
}