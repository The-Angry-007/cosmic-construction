#include "UnderGroundExit.hpp"
#include "Main.hpp"
#include "ResourceHandler.hpp"
#include "UnderGroundEnter.hpp"
#include "utils.hpp"

UndergroundExit::UndergroundExit(int id, int planetID, int direction)
{
	SetID(id);
	this->planetID = planetID;
	typeID = 11;
	SetDirection(direction);
	tileSize = ResourceHandler::structureSizes[typeID];
	sprite = sf::Sprite();
	ResourceHandler::structureAtlas->SetSprite(sprite, 11, direction + 4 * upgradeLevel);
	blocksItems = true;
	placedByPlayer = true;
	isConveyor = true;
	maxLength = 5;
	startBelt = -1;
}

void UndergroundExit::UpdateNeighbours()
{
	Planet& p = game->planets[planetID];
	startBelt = -1;
	sf::Vector2i pos = position + p.GetChunk(chunkID)->position * CHUNK_SIZE;
	for (int i = 1; i <= maxLength; i++)
	{
		sf::Vector2i offset = -CONVEYOR_OFFSETS[direction] * i;
		sf::Vector2i tilePos = pos + offset;
		int structure = p.StructureInPos(tilePos);
		if (structure != -1)
		{
			Structure* s = p.structures[structure];
			if (s->typeID == 10 && s->direction == direction)
			{
				startBelt = structure;
				break;
			}
		}
	}
}
void UndergroundExit::Update(float dt)
{
}

void UndergroundExit::Render()
{
	zindex = -32;
	Planet& p = game->planets[planetID];
	p.renderObjects.push_back(RenderObject {
		&sprite,
		zindex });
}

JSON UndergroundExit::ToJSON()
{
	JSON j = JSON();
	j.AddAttribute("PositionX", std::to_string(position.x));
	j.AddAttribute("PositionY", std::to_string(position.y));
	j.AddAttribute("TypeID", std::to_string(typeID));
	j.AddAttribute("Direction", std::to_string(direction));
	j.AddAttribute("ID", std::to_string(id));
	j.AddAttribute("ChunkID", std::to_string(chunkID));
	j.AddAttribute("UpgradeLevel", upgradeLevel);

	return j;
}
void UndergroundExit::FromJSON(JSON j)
{
	sf::Vector2i pos(0, 0);
	pos.x = std::stoi(j.GetValue("PositionX"));
	pos.y = std::stoi(j.GetValue("PositionY"));
	typeID = std::stoi(j.GetValue("TypeID"));
	SetUpgradeLevel(j.GetInt("UpgradeLevel"));
	direction = std::stoi(j.GetValue("Direction"));
	SetID(std::stoi(j.GetValue("ID")));
	chunkID = std::stoi(j.GetValue("ChunkID"));
	pos += game->planets[planetID].GetChunk(chunkID)->position * CHUNK_SIZE;

	ResourceHandler::structureAtlas->SetSprite(sprite, 11, direction + 4 * upgradeLevel);
	SetPosition(pos);
}

void UndergroundExit::SetDirection(int direction)
{
	this->direction = direction;
	ResourceHandler::structureAtlas->SetSprite(sprite, 11, direction + 4 * upgradeLevel);
}

UndergroundExit::~UndergroundExit()
{
	// delete hitbox;
}

void UndergroundExit::RenderPreview()
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
void UndergroundExit::Destroy()
{
}