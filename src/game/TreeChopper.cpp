#include "TreeChopper.hpp"
#include "Main.hpp"
#include "ResourceHandler.hpp"
TreeChopper::TreeChopper(int id, int planetID, int direction)
{
	SetID(id);
	this->planetID = planetID;
	typeID = 3;
	tileSize = ResourceHandler::structureSizes[typeID];
	sprite = sf::Sprite();
	SetDirection(direction);
	blocksItems = true;
	placedByPlayer = true;
	timeSinceAction = 0.f;
	//phase 0: waiting for tree to chop
	//phase 1: starting chop animation
	//phase 2: chopping down tree
	//phase 3: moving back
	phase = 0;
}
void TreeChopper::SetDirection(int direction)
{
	this->direction = direction;
	ResourceHandler::structureAtlas->SetSprite(sprite, typeID, direction * 15);
	phase = 0;
}
void TreeChopper::Update(float dt)
{
	timeSinceAction += dt;
	float timePerStep = 1.f;
	sf::Vector2i tilePos;
	Planet& p = game->planets[planetID];
	int index;
	if (phase == 0 || phase == 2)
	{
		tilePos = position + p.GetChunk(chunkID)->position * CHUNK_SIZE;
		tilePos += CONVEYOR_OFFSETS[direction];
		std::vector<int> structs = p.StructuresInArea(tilePos, sf::Vector2i(1, 1));
		index = -1;
		for (int i = 0; i < structs.size(); i++)
		{
			if (p.structures[structs[i]]->typeID == 4)
			{
				index = structs[i];
				break;
			}
			else if (p.structures[structs[i]]->typeID == 2)
			{
				index = structs[i];
			}
		}
	}
	if (phase == 0)
	{
		if (index != -1 && p.structures[index]->typeID == 2)
		{
			phase = 1;
			timeSinceAction = 0.f;
		}
		else if (index != -1 && p.structures[index]->typeID == 4)
		{
			SaplingPlanter* s = dynamic_cast<SaplingPlanter*>(p.structures[index]);
			if (s->tree != -1)
			{
				phase = 1;
				timeSinceAction = 0.f;
			}
		}
	}
	else if (phase == 1)
	{
		if (timeSinceAction > timePerStep)
		{
			phase = 2;
			timeSinceAction = 0.f;
		}
		else
		{
			int frame = (timeSinceAction / timePerStep) * 15;
			if (frame > 14)
			{
				frame = 14;
			}
			ResourceHandler::structureAtlas->SetSprite(sprite, typeID, direction * 15 + frame);
		}
	}
	else if (phase == 2)
	{
		ResourceHandler::structureAtlas->SetSprite(sprite, typeID, direction * 15 + 14);

		if (timeSinceAction > timePerStep)
		{
			if (index == -1)
			{
				phase = 3;
				timeSinceAction = 0.f;
				return;
			}
			if (p.structures[index]->typeID == 4)
			{
				SaplingPlanter* s = dynamic_cast<SaplingPlanter*>(p.structures[index]);
				for (int i = 0; i < p.structures.size(); i++)
				{
					if (p.structures[i] != nullptr && p.structures[i]->id == s->tree)
					{
						index = i;
						break;
					}
				}
				if (index == -1)
				{
					phase = 3;
					timeSinceAction = 0.f;
					return;
				}
				s->tree = -1;
			}
			if (p.structures[index]->typeID != 2)
			{
				phase = 3;
				timeSinceAction = 0.f;
				return;
			}
			dynamic_cast<Tree*>(p.structures[index])->Destroy();
			p.RemoveStructure(index);
			phase = 3;
			timeSinceAction = 0.f;
		}
	}
	else if (phase == 3)
	{
		if (timeSinceAction > timePerStep)
		{
			phase = 0;
			timeSinceAction = 0.f;
			ResourceHandler::structureAtlas->SetSprite(sprite, typeID, direction * 15);
		}
		else
		{
			int frame = (1 - timeSinceAction / timePerStep) * 15;
			ResourceHandler::structureAtlas->SetSprite(sprite, typeID, direction * 15 + frame);
		}
	}
}
void TreeChopper::Render()
{
	game->planets[planetID].renderObjects.push_back(RenderObject {
		&sprite,
		16 });
}
void TreeChopper::RenderPreview()
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

TreeChopper::~TreeChopper()
{}

JSON TreeChopper::ToJSON()
{
	JSON j = JSON();
	j.AddAttribute("Position", position);
	j.AddAttribute("ChunkID", chunkID);
	j.AddAttribute("TypeID", typeID);
	j.AddAttribute("ID", id);
	j.AddAttribute("Phase", phase);
	j.AddAttribute("Direction", direction);
	j.AddAttribute("TimeSinceAction", timeSinceAction);
	return j;
}
void TreeChopper::FromJSON(JSON j)
{
	sf::Vector2i pos = j.GetV2i("Position");
	chunkID = j.GetInt("ChunkID");
	id = j.GetInt("ID");
	phase = j.GetInt("Phase");
	direction = j.GetInt("Direction");
	timeSinceAction = j.GetFloat("TimeSinceAction");
	pos += game->planets[planetID].GetChunk(chunkID)->position * CHUNK_SIZE;
	SetPosition(pos);
	ResourceHandler::structureAtlas->SetSprite(sprite, typeID, direction * 15);
}