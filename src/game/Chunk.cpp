#include "Chunk.hpp"
#include "Main.hpp"

int CurrentChunkID = 0;

Chunk::Chunk(sf::Vector2i position, int id, int planetID)
{
	//the code below is deprecated, as a chunk's id now matches its position within the array of chunks.
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
	this->structures = {};
	this->planetID = planetID;
	this->position = position;
	hitbox = new Hitbox(sf::Vector2f(0.f, 0.f), sf::Vector2f(1.f, 1.f));
	sf::Vector2f halfSize = (sf::Vector2f)CHUNK_SIZE_PIXELS / 2.f;
	sf::Vector2f midpoint = GetWorldPos(halfSize);
	hitbox->AddShape(new HitboxRect(midpoint, halfSize * 1.1f));
	isDeleted = false;
}
//creates a blank chunk to fill an empty slot in the array of all chunks
Chunk::Chunk()
{
	isDeleted = true;
}
//update function is now deprecated as every structure and item is always updated
void Chunk::Update(float dt)
{
}
//converts position of chunk to world position
sf::Vector2f Chunk::GetWorldPos(sf::Vector2f position)
{
	return sf::Vector2f((float)this->position.x * CHUNK_SIZE_PIXELS.x, (float)this->position.y * CHUNK_SIZE_PIXELS.y) + position;
}
void Chunk::Render()
{
	//the commented out code below is used for debugging, it displays a rectangle whose colour shows the position of the chunk.
	//can be seen in most testing videos from iteration 2.

	// sf::RectangleShape chunkRect((sf::Vector2f)CHUNK_SIZE_PIXELS);
	// chunkRect.setFillColor(sf::Color(abs(position.x) * 25, abs(position.y) * 25, 0));
	// chunkRect.setPosition(GetWorldPos(sf::Vector2f(0, 0)));
	// window->draw(chunkRect);

	//renders all structures and items in the chunk.
	Planet* planet = &game->planets[planetID];
	for (int i = 0; i < structures.size(); i++)
	{
		planet->structures[structures[i]]->Render();
	}
	for (int i = 0; i < items.size(); i++)
	{
		planet->items[items[i]].Render(planet);
	}
}
//used to check which chunks should be rendered
bool Chunk::isVisible()
{
	return hitbox->intersects(game->planets[planetID].camera.hitbox);
}