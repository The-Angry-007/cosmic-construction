#include "Tree.hpp"
#include "Main.hpp"
#include "ResourceHandler.hpp"
Tree::Tree(int id, int planetID)
{
	SetID(id);
	this->planetID = planetID;
	typeID = 2;
	health = 3;
	tileSize = ResourceHandler::structureSizes[typeID];
	sprite = sf::Sprite();
	ResourceHandler::structureAtlas->SetSprite(sprite, 2, 0);
	blocksItems = true;
	placedByPlayer = false;
	parent = -1;
	isTerrain = true;
}

Tree ::~Tree()
{}

void Tree::Destroy()
{
	int numItems = 5;
	//get possible positions to place items
	std::vector<sf::Vector2i> possiblePositions = {};
	Planet& p = game->planets[planetID];
	sf::Vector2i pos = position + p.GetChunk(chunkID)->position * CHUNK_SIZE;
	for (int y = -1; y < 2; y++)
	{
		for (int x = -1; x < 2; x++)
		{
			sf::Vector2i position = pos + sf::Vector2i(x, y);
			std::vector<int> structures = p.StructuresInArea(position, sf::Vector2i(1, 1));
			bool canAdd = true;
			for (int i = 0; i < structures.size(); i++)
			{
				if (p.structures[structures[i]]->id != id && p.structures[structures[i]]->blocksItems)
				{
					canAdd = false;
					break;
				}
			}
			if (x == 0 && y == 0 && parent != -1)
			{
				canAdd = false;
			}
			if (canAdd)
			{
				possiblePositions.push_back(position);
			}
		}
	}
	if (possiblePositions.size() == 0)
	{
		possiblePositions.push_back(pos);
	}
	for (int i = 0; i < numItems; i++)
	{
		sf::Vector2f pos = (sf::Vector2f)possiblePositions[rand() % possiblePositions.size()];
		pos += sf::Vector2f(rand() % 1000, rand() % 1000) / 1000.f;
		pos.x *= TILE_SIZE.x;
		pos.y *= TILE_SIZE.y;
		Item item = Item(pos, -1, 0);
		item.SetParent(-1);
		p.AddItem(item);
		p.MoveItem(item.id);
		// p.items.push_back(Item(pos, -1, 0));
		// p.items.back().SetParent(-1);
		// p.MoveItem(p.items.size() - 1);
	}
}

void Tree::FromJSON(JSON j)
{
	sf::Vector2i pos = j.GetV2i("Position");
	chunkID = j.GetInt("ChunkID");
	position = pos + game->planets[planetID].GetChunk(chunkID)->position * CHUNK_SIZE;
	SetID(j.GetInt("ID"));
	SetPosition(position);
	health = j.GetInt("Health");
	parent = j.GetInt("Parent");
}
JSON Tree::ToJSON()
{
	JSON j = JSON();
	j.AddAttribute("Position", position);
	j.AddAttribute("ChunkID", chunkID);
	j.AddAttribute("TypeID", typeID);
	j.AddAttribute("ID", id);
	j.AddAttribute("Health", health);
	j.AddAttribute("Parent", parent);
	return j;
}
void Tree::Update(float dt)
{}
void Tree::Render()
{
	game->planets[planetID].renderObjects.push_back(RenderObject {
		&sprite,
		17 });
}