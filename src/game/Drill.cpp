#include "Drill.hpp"
#include "Main.hpp"
#include "ResourceHandler.hpp"
Drill::Drill(int id, int planetID, int direction)
{
	SetID(id);
	this->planetID = planetID;
	typeID = 6;
	tileSize = ResourceHandler::structureSizes[typeID];
	sprite = sf::Sprite();
	currentFrame = 0;
	ResourceHandler::structureAtlas->SetSprite(sprite, typeID, currentFrame);
	blocksItems = true;
	placedByPlayer = true;
	timePerFrame = 0.3333f;
	animProgress = 0.f;
	timeSinceOutput = 0.f;
	numStone = 0;
	neighbours = {};
	lastOutputDir = 0;
}

Drill::~Drill()
{}

void Drill::UpdateNeighbours()
{
	std::vector<sf::Vector2i> offsets = {
		{ 0, -1 },
		{ 1, -1 },
		{ -1, 0 },
		{ 2, 0 },
		{ -1, 1 },
		{ 2, 1 },
		{ 0, 2 },
		{ 1, 2 }
	};
	std::vector<int> directions = {
		2, 2, 1, 3, 1, 3, 0, 0
	};
	neighbours = {};
	Planet& p = game->planets[planetID];
	sf::Vector2i pos = position + p.GetChunk(chunkID)->position * CHUNK_SIZE;
	for (int i = 0; i < offsets.size(); i++)
	{
		sf::Vector2i newPos = pos + offsets[i];
		int structure = p.StructureInPos(newPos);
		if (structure != -1)
		{
			Structure* s = p.structures[structure];
			if (s->typeID == 0 && s->direction == ((directions[i] + 2) % 4))
			{
				neighbours.push_back(structure);
			}
			else
			{
				neighbours.push_back(-1);
			}
		}
		else
		{
			neighbours.push_back(-1);
		}
	}
}

void Drill::Update(float dt)
{
	animProgress += dt;
	if (animProgress > timePerFrame)
	{
		currentFrame = (currentFrame + 1) % 3;
		ResourceHandler::structureAtlas->SetSprite(sprite, typeID, currentFrame);
		animProgress = 0.f;
	}
	timeSinceOutput += dt;
	if (timeSinceOutput > 2.f)
	{
		for (int i = 0; i < 8; i++)
		{
			int index = (i + lastOutputDir) % 8;
			if (neighbours[index] != -1)
			{
				Conveyor* c = dynamic_cast<Conveyor*>(game->planets[planetID].structures[neighbours[index]]);
				int dir = (c->direction + 2) % 4;
				if (c->progress[dir].size() == 0 || c->progress[dir][c->progress[dir].size() - 1] > c->gap)
				{
					numStone = (numStone + 1) % 4;
					int output = (numStone == 0) ? 2 : 1;
					Item item = Item(sf::Vector2f(0.f, 0.f), -1, output);
					game->planets[planetID].items.push_back(item);
					c->items[dir].push_back(game->planets[planetID].items.size() - 1);
					c->progress[dir].push_back(0.f);
					lastOutputDir = (index + 1) % 8;
				}
			}
		}
	}
}

void Drill::Render()
{
	game->planets[planetID].renderObjects.push_back(RenderObject {
		&sprite,
		32 });
}

void Drill::RenderPreview()
{
	int opacity = 100;
	sf::Color col = sf::Color::Green;

	if (!CanBePlaced())
	{
		col = sf::Color(255, 100, 100);
	}
	col.a = opacity;
	sprite.setColor(col);
	Planet& p = game->planets[planetID];
	p.renderObjects.push_back(RenderObject {
		&sprite,
		2000 });
}

JSON Drill::ToJSON()
{
	return JSON();
}
void Drill::FromJSON(JSON j)
{
}