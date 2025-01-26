#include "StorageSilo.hpp"
#include "Main.hpp"
#include "ResourceHandler.hpp"
StorageSilo::StorageSilo(int id, int planetID, int direction)
{
	SetID(id);
	this->planetID = planetID;
	typeID = 1;
	for (int i = 0; i < 11; i++)
	{
		sf::Sprite s;
		ResourceHandler::structureAtlas->SetSprite(s, typeID, i);
		sprites.push_back(s);
	}
	this->sprite = sf::Sprite();
	tileSize = ResourceHandler::structureSizes[typeID];
	itemIDs = {};
	itemQuantities = {};
	previousOutputs = {};
	for (int i = 0; i < 12; i++)
	{
		previousOutputs.push_back(0);
	}
	blocksItems = false;
	placedByPlayer = true;
}

void StorageSilo::SetPosition(sf::Vector2i position)
{
	Structure::SetPosition(position);
	for (int i = 0; i < sprites.size(); i++)
	{
		sprites[i].setPosition(this->sprite.getPosition());
	}
	// UpdateNeighbours();
}

StorageSilo::~StorageSilo()
{
}

void StorageSilo::UpdateNeighbours()
{
	inputNeighbours = {};
	outputNeighbours = {};
	sf::Vector2i pos = position;
	pos += game->planets[planetID].GetChunk(chunkID)->position * CHUNK_SIZE;
	int targetLength = 0;
	std::vector<sf::Vector2i> offsets = {
		sf::Vector2i(0, -1),
		sf::Vector2i(1, -1),
		sf::Vector2i(2, -1),
		sf::Vector2i(-1, 0),
		sf::Vector2i(3, 0),
		sf::Vector2i(-1, 1),
		sf::Vector2i(3, 1),
		sf::Vector2i(-1, 2),
		sf::Vector2i(3, 2),
		sf::Vector2i(0, 3),
		sf::Vector2i(1, 3),
		sf::Vector2i(2, 3),
	};
	std::vector<int> directions = {
		2, 2, 2, 1, 3, 1, 3, 1, 3, 0, 0, 0
	};
	for (int i = 0; i < offsets.size(); i++)
	{

		targetLength++;
		int direction = directions[i];
		int neighbour = game->planets[planetID].StructureInPos(pos + offsets[i]);
		if (neighbour != -1 && game->planets[planetID].structures[neighbour]->isConveyor)
		{
			Structure* s = game->planets[planetID].structures[neighbour];
			if (s->direction == direction)
			{
				inputNeighbours.push_back(neighbour);
			}
			else if (s->direction == (direction + 2) % 4)
			{
				outputNeighbours.push_back(neighbour);
			}
		}
		if (inputNeighbours.size() != targetLength)
		{
			inputNeighbours.push_back(-1);
		}
		if (outputNeighbours.size() != targetLength)
		{
			outputNeighbours.push_back(-1);
		}
	}
}
void StorageSilo::TryAddGroundItem(int index)
{
	// Item* item = &game->planets[planetID].items[index];
	// Chunk* chunk = game->planets[planetID].GetChunk(item->chunkID);
	// for (int i = 0; i < chunk->items.size(); i++)
	// {
	// 	if (chunk->items[i] == index)
	// 	{
	// 		chunk->items.erase(chunk->items.begin() + i);
	// 		break;
	// 	}
	// }
	// item->parent = id;
	// item->SetParent(id);
	TryAddItem(index);
}
void StorageSilo::Update(float dt)
{
	// for (int i = 0; i < inputNeighbours.size(); i++)
	// {
	// 	if (inputNeighbours[i] == -1)
	// 	{
	// 		continue;
	// 	}
	// 	Conveyor* c = dynamic_cast<Conveyor*>(game->planets[planetID].structures[inputNeighbours[i]]);
	// 	if (c->items[c->direction].size() > 0 && c->progress[c->direction][0] >= 1.f)
	// 	{
	// 		AddItem(c->items[c->direction][0]);
	// 		c->items[c->direction].erase(c->items[c->direction].begin());
	// 		c->progress[c->direction].erase(c->progress[c->direction].begin());
	// 	}
	// }
	//WORKING HERE
	//NEED TO MAKE THIS USE THE NEW CONVEYORTYPE SYSTEM
	if (itemIDs.size() > 0)
	{
		for (int i = 0; i < outputNeighbours.size(); i++)
		{
			if (outputNeighbours[i] != -1)
			{
				previousOutputs[i] %= itemIDs.size();

				ConveyorType* c = dynamic_cast<ConveyorType*>(game->planets[planetID].structures[outputNeighbours[i]]);
				int dir = (c->direction + 2) % 4;
				Item item = Item(sf::Vector2f(0.f, 0.f), -1, itemIDs[previousOutputs[i]]);
				item.SetParent(1);
				game->planets[planetID].AddItem(item);
				int index = item.id;
				if (c->TryAddItem(index, dir, 0.f))
				{
					itemQuantities[previousOutputs[i]]--;
					if (itemQuantities[previousOutputs[i]] == 0)
					{
						itemQuantities.erase(itemQuantities.begin() + previousOutputs[i]);
						itemIDs.erase(itemIDs.begin() + previousOutputs[i]);
						if (itemIDs.size() == 0)
						{
							break;
						}
					}
					previousOutputs[i]++;
				}
			}
		}
	}
}
bool StorageSilo::TryAddItem(int index)
{
	int typeId = game->planets[planetID].items[index].typeId;
	game->planets[planetID].RemoveItem(index);
	bool existing = false;
	for (int i = 0; i < itemIDs.size(); i++)
	{
		if (itemIDs[i] == typeId)
		{
			existing = true;
			itemQuantities[i]++;
			break;
		}
	}
	if (!existing)
	{

		if (itemIDs.size() == 0 || typeId > itemIDs[itemIDs.size() - 1])
		{
			itemIDs.push_back(typeId);
			itemQuantities.push_back(1);
		}
		else
			for (uint i = 0; i < itemIDs.size(); i++)
			{
				if (typeId < itemIDs[i])
				{
					itemIDs.insert(itemIDs.begin() + i, typeId);
					itemQuantities.insert(itemQuantities.begin() + i, 1);
					break;
				}
			}
	}
	return true;
}
JSON StorageSilo::ToJSON()
{
	JSON j = JSON();
	j.AddAttribute("Position", position);
	j.AddAttribute("TypeID", typeID);
	j.AddAttribute("ID", id);
	j.AddAttribute("ChunkID", chunkID);
	j.AddAttribute("NumItemIDs", (int)itemIDs.size());
	for (int i = 0; i < itemIDs.size(); i++)
	{
		j.AddAttribute("ItemID" + std::to_string(i), itemIDs[i]);
		j.AddAttribute("ItemQuantity" + std::to_string(i), itemQuantities[i]);
	}
	return j;
}
void StorageSilo::FromJSON(JSON j)
{
	sf::Vector2i pos = j.GetV2i("Position");
	typeID = j.GetInt("TypeID");
	SetID(j.GetInt("ID"));
	chunkID = j.GetInt("ChunkID");
	pos += game->planets[planetID].GetChunk(chunkID)->position * CHUNK_SIZE;
	SetPosition(pos);
	int numIds = j.GetInt("NumItemIDs");
	for (int i = 0; i < numIds; i++)
	{
		itemIDs.push_back(j.GetInt("ItemID" + std::to_string(i)));
		itemQuantities.push_back(j.GetInt("ItemQuantity" + std::to_string(i)));
	}
}
void StorageSilo::Render()
{
	game->planets[planetID].renderObjects.push_back(RenderObject {
		&sprites[0],
		48 });
	game->planets[planetID].renderObjects.push_back(RenderObject {
		&sprites[1],
		49 });
	for (int i = 0; i < 9; i++)
	{
		if (inputNeighbours[i + 3] != -1 || outputNeighbours[i + 3] != -1)
		{

			game->planets[planetID].renderObjects.push_back(RenderObject {
				&sprites[i + 2],
				49 });
		}
	}
}

void StorageSilo::RenderPreview()
{
	int opacity = 100;
	sf::Color col = sf::Color::Green;
	if (!CanBePlaced())
	{
		col = sf::Color::Red;
	}
	col.a = opacity;
	sprites[0].setColor(col);
	sprites[1].setColor(col);
	game->planets[planetID]
		.renderObjects.push_back(RenderObject {
			&sprites[0],
			100 });
	game->planets[planetID].renderObjects.push_back(RenderObject {
		&sprites[1],
		101 });
}
void StorageSilo::SetVisualPosition(sf::Vector2i pos)
{
	Structure::SetVisualPosition(pos);
	for (uint i = 0; i < sprites.size(); i++)
	{
		sprites[i].setPosition(sprite.getPosition());
	}
}

void StorageSilo::Interact()
{
	SiloMenu* s = new SiloMenu(this);
	s->Update(0);
	guihandler.AddGUI(s);
}

void StorageSilo::Destroy()
{
	// for (int j = 0; j < items.size(); j++)
	// {
	// 	Item& item = game->planets[planetID].items[items[j]];
	// 	item.SetParent(-1);
	// 	item.position = (sf::Vector2f)(position + game->planets[planetID].GetChunk(chunkID)->position * CHUNK_SIZE);
	// 	item.position += sf::Vector2f(rand() % 1000 * tileSize.x, rand() % 1000 * tileSize.y) / 1000.f;
	// 	item.position.x *= TILE_SIZE.x;
	// 	item.position.y *= TILE_SIZE.y;
	// 	game->planets[planetID].MoveItem(items[j]);
	// }
	for (int i = 0; i < itemIDs.size(); i++)
	{
		for (int j = 0; j < itemQuantities[i]; j++)
		{
			Item item = Item(sf::Vector2f(0.f, 0.f), -1, itemIDs[i]);
			game->planets[planetID].AddItem(item);
			item.SetParent(-1);
			item.SetParent(-1);
			item.position = (sf::Vector2f)(position + game->planets[planetID].GetChunk(chunkID)->position * CHUNK_SIZE);
			item.position += sf::Vector2f(rand() % 1000 * tileSize.x, rand() % 1000 * tileSize.y) / 1000.f;
			item.position.x *= TILE_SIZE.x;
			item.position.y *= TILE_SIZE.y;
			game->planets[planetID].MoveItem(item.id);
		}
	}
}