#include "Planet.hpp"
#include "InputHandler.hpp"
#include "Main.hpp"
#include "binds.hpp"
#define sh SaveHandler

Planet::Planet(int id)
{
	this->id = id;
	if (id == 0)
	{
		backgroundColor = sf::Color(90, 128, 62);
	}
	draggingItem = -1;
	hoveringItem = -1;
	mouseStartDraggingPos = sf::Vector2f(0.f, 0.f);
	itemStartDraggingPos = sf::Vector2f(0.f, 0.f);
	chunks = {};
	items = {};
	camera = Camera();
}
void Planet::Init(bool load)
{
	if (load)
	{
		std::string path = sh::workingDir + "\\planets\\" + std::to_string(id) + "\\";
		savePath = path;
		//load items
		std::string chunkPath = path + "chunks.txt";
		Table chunkTable = Table();
		chunkTable.FromString(sh::ReadData(chunkPath));
		for (uint i = 0; i < chunkTable.records.size(); i++)
		{
			sf::Vector2i pos(0, 0);
			pos.x = std::stoi(chunkTable.GetValue("PositionX", i));
			pos.y = std::stoi(chunkTable.GetValue("PositionY", i));
			int id = std::stoi(chunkTable.GetValue("ChunkID", i));
			Chunk c = Chunk(pos, id, this->id);
			chunks.push_back(c);
		}
		//loading items
		std::string itemPath = path + "items.txt";
		Table itemTable = Table();
		itemTable.FromString(sh::ReadData(itemPath));
		for (uint i = 0; i < itemTable.records.size(); i++)
		{
			sf::Vector2f pos(0, 0);
			pos.x = std::stof(itemTable.GetValue("PositionX", i));
			pos.y = std::stof(itemTable.GetValue("PositionY", i));
			int id = std::stoi(itemTable.GetValue("ItemID", i));
			int typeId = std::stoi(itemTable.GetValue("TypeID", i));
			Item item = Item(pos, id, typeId);
			items.push_back(item);
			//TODO: DEAL WITH PARENT ATTRIBUTE
			MoveItem(items.size() - 1);
		}
		//loading camera
		{
			JSON camjson = JSON();
			camjson.FromString(SaveHandler::ReadData(path + "camera.txt"));
			sf::Vector2f pos(0, 0);
			pos.x = std::stof(camjson.GetValue("PositionX"));
			pos.y = std::stof(camjson.GetValue("PositionY"));
			camera.position = pos;
			camera.zoom = std::stof(camjson.GetValue("Zoom"));
			camera.targetZoom = camera.zoom;
		}
	}
	else
	{
		int numItems = 10000;
		// chunks.push_back(Chunk(sf::Vector2i(0, 0), -1, this->id));
		GenerateChunksInView();
		for (uint i = 0; i < numItems; i++)
		{
			int size = 1000;
			items.push_back(Item(sf::Vector2f(rand() % (size * 2) - size, rand() % (size * 2) - size),
				-1,
				rand() % ResourceHandler::numItems));
			MoveItem(items.size() - 1);
		}
	}
	structure = new Structure(sf::Vector2i(0, 0), 0, -1, 0, 0);
}
void Planet::Update(float dt)
{
	camera.Update(dt);
	GenerateChunksInView();
	if (hoveringItem != -1)
	{
		ResourceHandler::itemAtlas->SetSprite(items[hoveringItem].sprite, items[hoveringItem].typeId);
	}
	if (draggingItem == -1)
	{
		bool end = false;
		for (int i = items.size() - 1; i > -1; i--)
		{

			if (items[i].accurateHitbox->intersectsPoint(camera.WorldMousePos()))
			{

				if (InputHandler::pressed(binds::DragItem))
				{
					draggingItem = i;
					mouseStartDraggingPos = camera.WorldMousePos();
					itemStartDraggingPos = items[i].position;
				}
				else if (!InputHandler::down(binds::DragItem))
				{
					hoveringItem = i;
					ResourceHandler::itemAtlas->SetSprite(items[hoveringItem].sprite, items[hoveringItem].typeId + ResourceHandler::numItems);
				}
				end = true;
				break;
			}
		}
	}
	else
	{
		if (!InputHandler::down(binds::DragItem))
		{
			draggingItem = -1;
		}
		else
		{
			sf::Vector2f offset = camera.WorldMousePos() - mouseStartDraggingPos;
			items[draggingItem].position = itemStartDraggingPos + offset;
			MoveItem(draggingItem);
		}
	}
	for (uint i = 0; i < chunks.size(); i++)
	{

		chunks[i].Update(dt);
	}
	structure->Update(dt);
}

void Planet::Render()
{
	sf::FloatRect camRect = camera.toFloatRect();
	sf::RectangleShape rect(sf::Vector2f(camRect.width, camRect.height));
	rect.setPosition(camRect.left, camRect.top);
	rect.setFillColor(backgroundColor);
	window->draw(rect);
	for (uint i = 0; i < chunks.size(); i++)
	{
		if (chunks[i].isVisible())
			chunks[i].Render();
	}
	structure->Render();
}

void Planet::Save()
{
	std::string path = sh::workingDir + "\\planets";
	if (!sh::DirExists(path))
	{
		sh::CreateDirectoryW(path);
	}
	path += "\\" + std::to_string(id);
	if (!sh::DirExists(path))
	{
		sh::CreateDirectory(path);
	}
	//items
	Table itemTable = Table();
	itemTable.headers = { "ItemID", "TypeID", "PositionX", "PositionY", "Parent" };
	for (int i = 0; i < items.size(); i++)
	{
		itemTable.records.push_back({ std::to_string(items[i].id),
			std::to_string(items[i].typeId),
			std::to_string(items[i].position.x),
			std::to_string(items[i].position.y),
			"-1" });
	}
	sh::WriteData(path + "\\items.txt", itemTable.ToString());
	//camera
	JSON camjson = JSON();
	camjson.AddAttribute("PositionX", std::to_string(camera.position.x));
	camjson.AddAttribute("PositionY", std::to_string(camera.position.y));
	camjson.AddAttribute("Zoom", std::to_string(camera.zoom));
	sh::WriteData(path + "\\camera.txt", camjson.ToString());
	//chunks
	Table chunkTable = Table();
	chunkTable.headers = { "ChunkID", "PositionX", "PositionY" };
	for (int i = 0; i < chunks.size(); i++)
	{
		chunkTable.records.push_back({ std::to_string(chunks[i].id),
			std::to_string(chunks[i].position.x),
			std::to_string(chunks[i].position.y) });
	}
	sh::WriteData(path + "\\chunks.txt", chunkTable.ToString());
}

void Planet::GenerateChunk(sf::Vector2i position)
{
	Chunk c = Chunk(position, -1, id);
	chunks.push_back(c);
}
void Planet::GenerateChunksInView()
{
	HitboxShape* hitbox = camera.hitbox->shapes[0];
	sf::Vector2f topleft = hitbox->currentPos - hitbox->currentSize;
	sf::Vector2i minPos((int)floor(topleft.x / CHUNK_SIZE_PIXELS.x), (int)floor(topleft.y / CHUNK_SIZE_PIXELS.y));
	sf::Vector2f bottomright = hitbox->currentPos + hitbox->currentSize;
	sf::Vector2i maxPos((int)ceil(bottomright.x / CHUNK_SIZE_PIXELS.x), (int)ceil(bottomright.y / CHUNK_SIZE_PIXELS.y));
	for (int x = minPos.x; x <= maxPos.x; x++)
	{
		for (int y = minPos.y; y <= maxPos.y; y++)
		{
			bool exists = false;
			for (int i = 0; i < chunks.size(); i++)
			{
				if (chunks[i].position.x == x && chunks[i].position.y == y)
				{
					exists = true;
					continue;
				}
			}
			if (!exists)
				GenerateChunk(sf::Vector2i(x, y));
		}
	}
}

void Planet::MoveItem(int index)
{
	Item* item = &items[index];
	if (item->chunkID != -1)
	{
		Chunk* c = &chunks[item->chunkID];
		for (uint i = 0; i < c->items.size(); i++)
		{
			if (c->items[i] == index)
			{
				c->items.erase(c->items.begin() + i);
				break;
			}
		}
	}
	sf::Vector2f chunkPos(item->position.x / CHUNK_SIZE_PIXELS.x, item->position.y / CHUNK_SIZE_PIXELS.y);
	sf::Vector2i chunkCoords((int)floor(chunkPos.x), (int)floor(chunkPos.y));
	bool sorted = false;
	for (uint i = 0; i < chunks.size(); i++)
	{
		if (chunks[i].position.x == chunkCoords.x && chunks[i].position.y == chunkCoords.y)
		{
			chunks[i].items.push_back(index);
			item->chunkID = chunks[i].id;
			sorted = true;

			break;
		}
	}
	if (!sorted)
	{
		GenerateChunk(chunkCoords);
		uint i = chunks.size() - 1;
		chunks[i].items.push_back(index);
		item->chunkID = chunks[i].id;
	}
}
Chunk* Planet::GetChunk(int chunkID)
{
	for (uint i = 0; i < chunks.size(); i++)
	{
		if (chunks[i].id == chunkID)
		{
			return &chunks[i];
		}
	}
	return nullptr;
}