#include "Planet.hpp"
#include "InputHandler.hpp"
#include "Main.hpp"
#include "binds.hpp"
#define sh SaveHandler

Planet::Planet(int id)
{
	structures = {};
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
			item.SetParent(std::stoi(itemTable.GetValue("Parent", i)));
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
		//loading structures
		{
			std::string structureData = sh::ReadData(path + "structures.txt");
			std::vector<JSON> jsons = sh::StringToJSONs(structureData);
			for (uint i = 0; i < jsons.size(); i++)
			{
				if (jsons[i].GetValue("TypeID") == "0")
				{
					Conveyor* c = new Conveyor(id);
					structures.push_back(c);
					c->FromJSON(jsons[i]);
				}
			}
		}
	}
	else
	{
		int numItems = 1000;
		// chunks.push_back(Chunk(sf::Vector2i(0, 0), -1, this->id));
		GenerateChunksInView();
		for (uint i = 0; i < numItems; i++)
		{
			int size = 100;
			items.push_back(Item(sf::Vector2f(rand() % (size * 2) - size, rand() % (size * 2) - size),
				-1,
				rand() % ResourceHandler::numItems));
			items[items.size() - 1].SetParent(-1);
			MoveItem(items.size() - 1);
		}
	}
	placeDir = 0;
}
void Planet::Update(float dt)
{
	camera.Update(dt);
	GenerateChunksInView();
	if (hoveringItem != -1)
	{
		ResourceHandler::itemAtlas->SetSprite(items[hoveringItem].sprite, items[hoveringItem].typeId);
	}
	if (draggingItem == -1 && game->toolHandler->selectedTool == 1)
	{
		bool end = false;
		for (int i = items.size() - 1; i > -1; i--)
		{
			if (items[i].parent != -1)
			{
				continue;
			}
			if (items[i].accurateHitbox->intersectsPoint(camera.WorldMousePos()) && !InputHandler::mouseIsBlocked)
			{

				if (InputHandler::pressed(binds::UseTool))
				{
					draggingItem = i;
					mouseStartDraggingPos = camera.WorldMousePos();
					itemStartDraggingPos = items[i].position;
				}
				else if (!InputHandler::down(binds::UseTool))
				{
					hoveringItem = i;
					ResourceHandler::itemAtlas->SetSprite(items[hoveringItem].sprite, items[hoveringItem].typeId + ResourceHandler::numItems);
				}
				end = true;
				break;
			}
		}
	}
	else if (game->toolHandler->selectedTool == 1)
	{
		if (!InputHandler::down(binds::UseTool))
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
	for (uint i = 0; i < items.size(); i++)
	{
		items[i].Update(dt);
	}
	for (uint i = 0; i < structures.size(); i++)
	{
		structures[i]->Update(dt);
	}
	if (InputHandler::down(binds::UseTool) && game->toolHandler->selectedTool == 0)
	{
		sf::Vector2f mousePos = camera.WorldMousePos();
		sf::Vector2i tilePos(floor(mousePos.x / TILE_SIZE.x), floor(mousePos.y / TILE_SIZE.y));

		if (StructureInPos(tilePos) == -1)
		{
			Conveyor* s = new Conveyor(-1, id, placeDir);
			structures.push_back(s);

			s->SetPosition(tilePos);
		}
	}

	if (InputHandler::keyPressed(sf::Keyboard::Key::Right))
	{
		placeDir++;
		if (placeDir == 4)
		{
			placeDir = 0;
		}
	}
}

void Planet::Render()
{
	renderObjects = {};
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
	std::sort(renderObjects.begin(), renderObjects.end());
	for (uint i = 0; i < renderObjects.size(); i++)
	{
		window->draw(*renderObjects[i].sprite);
	}
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
			std::to_string(items[i].parent) });
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
	//structures
	std::vector<JSON> sJSONs;
	for (int i = 0; i < structures.size(); i++)
	{
		sJSONs.push_back(structures[i]->ToJSON());
	}
	std::string structureData = sh::JSONsToString(sJSONs);
	sh::WriteData(path + "\\structures.txt", structureData);
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
	int chunk = ChunkAtPos(item->position);
	chunks[chunk].items.push_back(index);
	item->chunkID = chunks[chunk].id;
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

int Planet::StructureInPos(sf::Vector2i position)
{
	sf::Vector2i chunkPos(
		floor((float)position.x / (float)CHUNK_SIZE),
		floor((float)position.y / (float)CHUNK_SIZE));
	// position -= sf::Vector2i(chunkPos.x * CHUNK_SIZE, chunkPos.y * CHUNK_SIZE);
	//need to also check the chunks left and up
	for (int x = chunkPos.x - 1; x <= chunkPos.x; x++)
	{
		for (int y = chunkPos.y - 1; y <= chunkPos.y; y++)
		{
			int chunk = -1;
			for (uint i = 0; i < chunks.size(); i++)
			{
				if (chunks[i].position.x == x && chunks[i].position.y == y)
				{
					chunk = i;
				}
			}
			if (chunk == -1)
			{
				continue;
			}
			for (uint i = 0; i < chunks[chunk].structures.size(); i++)
			{
				Structure* s = structures[chunks[chunk].structures[i]];
				sf::Vector2i pos = s->position + sf::Vector2i(x * CHUNK_SIZE, y * CHUNK_SIZE);
				sf::Vector2i pos2 = s->bottomRightPos + sf::Vector2i(x * CHUNK_SIZE, y * CHUNK_SIZE);
				// if (x == 0 && y == 0)
				// {
				// 	std::cout << "position is:" << pos.x << " " << pos.y << std::endl;
				// 	std::cout << "position2 is:" << pos2.x << " " << pos2.y << std::endl;
				// }
				if (pos.x <= position.x && pos.y <= position.y)
				{
					if (pos2.x >= position.x && pos2.y >= position.y)
					{
						return chunks[chunk].structures[i];
					}
				}
			}
		}
	}
	return -1;
}

int Planet::ChunkAtPos(sf::Vector2f position)
{
	sf::Vector2f chunkPosf(
		position.x / CHUNK_SIZE_PIXELS.x,
		position.y / CHUNK_SIZE_PIXELS.y);
	sf::Vector2i chunkPos(floor(chunkPosf.x), floor(chunkPosf.y));
	for (uint i = 0; i < chunks.size(); i++)
	{
		if (chunks[i].position == chunkPos)
		{
			return i;
		}
	}
	GenerateChunk(chunkPos);
	return chunks.size() - 1;
}
int Planet::ChunkAtPos(sf::Vector2i position)
{
	sf::Vector2f chunkPosf = (sf::Vector2f)position / (float)CHUNK_SIZE;
	sf::Vector2i chunkPos(floor(chunkPosf.x), floor(chunkPosf.y));
	for (uint i = 0; i < chunks.size(); i++)
	{
		if (chunks[i].position == chunkPos)
		{
			return i;
		}
	}
	GenerateChunk(chunkPos);
	return chunks.size() - 1;
}

sf::Vector2i Planet::tilePos(sf::Vector2f position)
{
	return sf::Vector2i(floor(position.x / TILE_SIZE.x), floor(position.y / TILE_SIZE.y));
}

sf::Vector2f Planet::worldPos(sf::Vector2f tilePos, int chunkID)
{
	auto chunk = GetChunk(chunkID);
	sf::Vector2f pos = (sf::Vector2f)chunk->position;

	pos.x *= (float)CHUNK_SIZE_PIXELS.x;
	pos.y *= (float)CHUNK_SIZE_PIXELS.y;

	pos += sf::Vector2f(tilePos.x * TILE_SIZE.x, tilePos.y * TILE_SIZE.y);

	return pos;
}