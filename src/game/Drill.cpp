#include "Drill.hpp"
#include "Main.hpp"
#include "Recipe.hpp"
#include "RecipeHandler.hpp"
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
	groundSprite = sf::Sprite();
	ResourceHandler::structureAtlas->SetSprite(groundSprite, typeID, 3);

	blocksItems = true;
	placedByPlayer = true;
	timePerFrame = 0.3333f;
	animProgress = 0.f;
	timeSinceOutput = 0.f;
	numStone = 0;
	neighbours = {};
	lastOutputDir = 0;
	outputItem = -1;
}

Drill::~Drill()
{}

void Drill::UpdateNeighbours()
{
	std::vector<sf::Vector2i> offsets = {
		{ 0, -1 },
		{ 1, -1 },
		{ 2, 0 },
		{ 2, 1 },
		{ 1, 2 },
		{ 0, 2 },
		{ -1, 1 },
		{ -1, 0 }
	};
	std::vector<int> directions = {
		2, 2, 3, 3, 0, 0, 1, 1
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
			if (s->typeID == 0 && s->direction != ((directions[i]) % 4))
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
	UpdateNeighbours();

	animProgress += dt;
	if (animProgress > timePerFrame)
	{
		currentFrame = (currentFrame + 1) % 3;
		ResourceHandler::structureAtlas->SetSprite(sprite, typeID, currentFrame);
		animProgress = 0.f;
	}
	timeSinceOutput += dt;
	std::vector<int> directions = {
		2, 2, 3, 3, 0, 0, 1, 1
	};
	if (outputItem == -1 && recipe != nullptr)
	{
		outputItem = recipe->TryTakeItem();
	}
	if (outputItem != -1)
	{
		for (int i = 0; i < 8; i++)
		{
			int index = (i + lastOutputDir) % 8;
			if (neighbours[index] != -1)
			{
				ConveyorType* c = dynamic_cast<ConveyorType*>(game->planets[planetID].structures[neighbours[index]]);
				int dir = directions[index];

				if (c->TryAddItem(outputItem, dir, 0.f))
				{
					outputItem = -1;
					timeSinceOutput = 0.f;
					lastOutputDir = (index + 1) % 8;
					timeSinceOutput = 0.f;
					break;
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
	game->planets[planetID].renderObjects.push_back(RenderObject {
		&groundSprite,
		-32 });
}

void Drill::Destroy()
{
	if (recipe != nullptr)
	{
		recipe->Destroy(this);
	}
}
void Drill::SetPosition(sf::Vector2i position)
{
	Structure::SetPosition(position);
	groundSprite.setPosition(sprite.getPosition());
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
	groundSprite.setColor(col);
	Planet& p = game->planets[planetID];
	p.renderObjects.push_back(RenderObject {
		&sprite,
		2000 });
	p.renderObjects.push_back(RenderObject {
		&groundSprite,
		1999 });
}

JSON Drill::ToJSON()
{
	JSON j = JSON();
	j.AddAttribute("Position", position);
	j.AddAttribute("TypeID", typeID);
	j.AddAttribute("ChunkID", chunkID);
	j.AddAttribute("ID", id);
	j.AddAttribute("NumStone", numStone);
	j.AddAttribute("TimeSinceOutput", timeSinceOutput);
	j.AddAttribute("AnimProgress", animProgress);
	j.AddAttribute("TimePerFrame", timePerFrame);
	j.AddAttribute("CurrentFrame", currentFrame);
	j.AddAttribute("LastOutputDir", lastOutputDir);
	j.AddAttribute("OutputItem", outputItem);
	return j;
}
void Drill::FromJSON(JSON j)
{
	sf::Vector2i pos = j.GetV2i("Position");
	chunkID = j.GetInt("ChunkID");
	id = j.GetInt("ID");
	pos += game->planets[planetID].GetChunk(chunkID)->position * CHUNK_SIZE;
	SetPosition(pos);
	numStone = j.GetInt("NumStone");
	timeSinceOutput = j.GetFloat("TimeSinceOutput");
	animProgress = j.GetFloat("AnimProgress");
	timePerFrame = j.GetFloat("TimePerFrame");
	currentFrame = j.GetInt("CurrentFrame");
	lastOutputDir = j.GetInt("LastOutputDir");
	outputItem = j.GetInt("OutputItem");
}

void Drill::SetVisualPosition(sf::Vector2i position)
{
	Structure::SetVisualPosition(position);
	groundSprite.setPosition(sprite.getPosition());
}

void Drill::Interact()
{
	int index = -1;
	Planet& p = game->planets[planetID];
	for (int i = 0; i < p.structures.size(); i++)
	{
		if (p.structures[i] == this)
		{
			index = i;
			break;
		}
	}
	RecipeHandler::InitGUI(index);
}

bool Drill::TryAddItem(int index)
{
	if (recipe == nullptr)
	{
		return false;
	}
	return recipe->TryAddItem(index);
}