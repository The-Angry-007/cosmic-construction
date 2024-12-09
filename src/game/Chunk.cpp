#include "Chunk.hpp"
#include "Main.hpp"

int CurrentChunkID = 0;

Chunk::Chunk(sf::Vector2i position, int id, int planetID)
{
	if (id == -1)
	{
		this->id = CurrentChunkID++;
	}
	else
	{
		this->id = id;
		if (this->id >= CurrentChunkID)
		{
			CurrentChunkID = this->id + 1;
		}
	}
	this->items = {};
	this->planetID = planetID;
	this->position = position;
	hitbox = new Hitbox(sf::Vector2f(0.f, 0.f), sf::Vector2f(1.f, 1.f));
	sf::Vector2f halfSize = sf::Vector2f(CHUNK_SIZE_PIXELS / 2.f, CHUNK_SIZE_PIXELS / 2.f);
	sf::Vector2f midpoint = GetWorldPos(halfSize);
	hitbox->AddShape(new HitboxRect(midpoint, halfSize * 1.1f));
}

void Chunk::Update(float dt)
{
	for (int i = 0; i < items.size(); i++)
	{
		game->planets[planetID].items[items[i]].Update(dt);
	}
}
sf::Vector2f Chunk::GetWorldPos(sf::Vector2f position)
{
	return ((sf::Vector2f)this->position) * (float)CHUNK_SIZE_PIXELS + position;
}
void Chunk::Render()
{
	sf::RectangleShape chunkRect(sf::Vector2f(CHUNK_SIZE_PIXELS, CHUNK_SIZE_PIXELS));
	chunkRect.setFillColor(sf::Color(abs(position.x) * 25, abs(position.y) * 25, 0));
	chunkRect.setPosition(GetWorldPos(sf::Vector2f(0, 0)));
	window->draw(chunkRect);
	Planet* planet = &game->planets[planetID];
	for (int i = 0; i < items.size(); i++)
	{
		planet->items[items[i]].Render();
		if (planet->items[items[i]].selectedSprite)
		{
			chunkRect.setFillColor(sf::Color(abs(position.x) * 25, abs(position.y) * 25, 0, 100));

			window->draw(chunkRect);
		}
	}
}

bool Chunk::isVisible()
{
	return hitbox->intersects(game->planets[planetID].camera.hitbox);
}