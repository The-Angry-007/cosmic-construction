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
//gets output neighbours around the drill
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
			if (s->isConveyor && ((s->direction == (directions[i] + 2) % 4) || s->direction == -1))
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
	//update recipe if there is one set
	if (recipe != nullptr)
	{
		recipe->Update(dt);
	}
	//progress drill bit animation
	animProgress += dt;
	if (animProgress > timePerFrame)
	{
		currentFrame = (currentFrame + 1) % 3;
		ResourceHandler::structureAtlas->SetSprite(sprite, typeID, currentFrame);
		animProgress = 0.f;
	}
	std::vector<int> directions = {
		2, 2, 3, 3, 0, 0, 1, 1
	};
	//attempt to output item
	if (recipe != nullptr)
	{
		for (int i = 0; i < 8; i++)
		{
			int index = (i + lastOutputDir) % 8;
			if (neighbours[index] != -1)
			{
				ConveyorType* c = dynamic_cast<ConveyorType*>(game->planets[planetID].structures[neighbours[index]]);
				int dir = directions[index];

				if (c->CanAddItem(dir, 0.f))
				{
					//take output item from recipe
					outputItem = recipe->TryTakeItem();
					if (outputItem != -1)
					{
						//insert in conveyor
						c->TryAddItem(outputItem, dir, 0.f);
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
}
//draw the dirt texture and the drill texture
void Drill::Render()
{
	game->planets[planetID].renderObjects.push_back(RenderObject {
		&sprite,
		32 });
	game->planets[planetID].renderObjects.push_back(RenderObject {
		&groundSprite,
		-32 });
}
//call destroy function for the recipe
void Drill::Destroy()
{
	if (recipe != nullptr)
	{
		recipe->Destroy(this);
	}
}
//calls the base class's corresponding function, then updates position of ground sprite
void Drill::SetPosition(sf::Vector2i position)
{
	Structure::SetPosition(position);
	groundSprite.setPosition(sprite.getPosition());
}
//draws drill as either red or ground depending on whether it can be placed
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
//converts data to JSON object
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
	if (recipe != nullptr)
	{
		j.AddAttribute("HasRecipe", 1);
		//if the drill has a recipe, the attributes of the recipe are appended
		j.AddJSON(recipe->ToJSON());
	}
	else
	{
		j.AddAttribute("HasRecipe", 0);
	}
	return j;
}
//loads from JSON object
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
	if (j.GetInt("HasRecipe"))
	{
		int id = j.GetInt("RecipeID");
		//creates new recipe object which loads from the same JSON object
		recipe = new Recipe(planetID, RecipeHandler::GetRecipe(id));
		recipe->FromJSON(j);
	}
}
//updates position without adding to a chunk etc.
void Drill::SetVisualPosition(sf::Vector2i position)
{
	Structure::SetVisualPosition(position);
	groundSprite.setPosition(sprite.getPosition());
}
//opens the recipe's GUI when interacted with
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
//calls recipe's try add item function
bool Drill::TryAddItem(int index)
{
	if (recipe == nullptr)
	{
		return false;
	}
	return recipe->TryAddItem(index);
}