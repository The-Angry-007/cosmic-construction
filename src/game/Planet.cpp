#include "Planet.hpp"
#include "InputHandler.hpp"
#include "Main.hpp"
#include "RandomHandler.hpp"
#include "binds.hpp"
#include "utils.hpp"
#define sh SaveHandler
#include "PerlinNoise.hpp"
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

	chunks = {};
	items = {};

	camera = Camera();
	camera.position = sf::Vector2f(32 * 17, 32 * 17);
	structuresToUpdate = {};
	emptyStructureSlots = {};
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
					Conveyor* c = new Conveyor(-2, id, 0);
					AddStructure(c);
					c->FromJSON(jsons[i]);
				}
				else if (jsons[i].GetValue("TypeID") == "1")
				{
					StorageSilo* s = new StorageSilo(-2, id);
					AddStructure(s);
					s->FromJSON(jsons[i]);
				}
				else if (jsons[i].GetValue("TypeID") == "2")
				{
					Tree* t = new Tree(-2, id);
					AddStructure(t);
					t->FromJSON(jsons[i]);
				}
				else if (jsons[i].GetValue("TypeID") == "3")
				{
					TreeChopper* t = new TreeChopper(-2, id, 0);
					AddStructure(t);
					t->FromJSON(jsons[i]);
				}
				else if (jsons[i].GetValue("TypeID") == "4")
				{
					SaplingPlanter* t = new SaplingPlanter(-2, id, 0);
					AddStructure(t);
					t->FromJSON(jsons[i]);
				}
				else if (jsons[i].GetValue("TypeID") == "5")
				{
					Boulder* t = new Boulder(-2, id);
					AddStructure(t);
					t->FromJSON(jsons[i]);
				}
			}
		}
	}
	else
	{
		// chunks.push_back(Chunk(sf::Vector2i(0, 0), -1, this->id));
		GenerateChunksInView();
	}
}
void Planet::Update(float dt)
{

	camera.Update(dt);
	GenerateChunksInView();

	// if (InputHandler::pressed(binds::Interact))
	// {
	// 	sf::Vector2f wmp = camera.WorldMousePos();
	// 	sf::Vector2i mouseTilePos(floor(wmp.x / TILE_SIZE.x), floor(wmp.y / TILE_SIZE.y));
	// 	int s = StructureInPos(mouseTilePos);
	// 	if (s != -1)
	// 	{
	// 		structures[s]->Interact();
	// 	}
	// }
}

void buildVertexArray(const std::vector<RenderObject>& renderObjects, sf::VertexArray& vertexArray)
{
	// Set the vertex array to quads and resize it to fit all sprites
	vertexArray.setPrimitiveType(sf::Quads);
	vertexArray.resize(renderObjects.size() * 4);

	for (size_t i = 0; i < renderObjects.size(); ++i)
	{
		const RenderObject& obj = renderObjects[i];
		const sf::Sprite* sprite = obj.sprite;

		// Extract texture rectangle and position
		const sf::FloatRect globalBounds = sprite->getGlobalBounds();
		const sf::IntRect textureRect = sprite->getTextureRect();

		// Calculate quad vertices
		sf::Vertex* quad = &vertexArray[i * 4];

		// Top-left
		quad[0].position = sf::Vector2f(globalBounds.left, globalBounds.top);
		quad[0].texCoords = sf::Vector2f(textureRect.left, textureRect.top);
		quad[0].color = sprite->getColor();

		// Top-right
		quad[1].position = sf::Vector2f(globalBounds.left + globalBounds.width, globalBounds.top);
		quad[1].texCoords = sf::Vector2f(textureRect.left + textureRect.width, textureRect.top);
		quad[1].color = sprite->getColor();

		// Bottom-right
		quad[2].position = sf::Vector2f(globalBounds.left + globalBounds.width, globalBounds.top + globalBounds.height);
		quad[2].texCoords = sf::Vector2f(textureRect.left + textureRect.width, textureRect.top + textureRect.height);
		quad[2].color = sprite->getColor();

		// Bottom-left
		quad[3].position = sf::Vector2f(globalBounds.left, globalBounds.top + globalBounds.height);
		quad[3].texCoords = sf::Vector2f(textureRect.left, textureRect.top + textureRect.height);
		quad[3].color = sprite->getColor();
	}
	sf::RenderStates states;
	states.texture = &ResourceHandler::completeAtlas->texture;

	window->draw(vertexArray, states);
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

	if (renderObjects.size() > 0)
	{
		std::sort(renderObjects.begin(), renderObjects.end());
		buildVertexArray(renderObjects, vertexArray);
		// for (uint i = 0; i < renderObjects.size(); i++)
		// {
		// 	window->draw(*renderObjects[i].sprite);
		// }
	}
	renderObjects = {};
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
		if (structures[i] == nullptr)
		{
			continue;
		}
		sJSONs.push_back(structures[i]->ToJSON());
	}
	std::string structureData = sh::JSONsToString(sJSONs);
	sh::WriteData(path + "\\structures.txt", structureData);
}

void Planet::GenerateChunk(sf::Vector2i position)
{
	Chunk c = Chunk(position, -1, id);
	chunks.push_back(c);

	if (position == sf::Vector2i(0, 0))
	{
		StorageSilo* s = new StorageSilo(-1, id);
		s->placedByPlayer = false;
		AddStructure(s);
		s->SetPosition(sf::Vector2i(16, 16));
		for (int i = 0; i < 10; i++)
		{
			Item item = Item(sf::Vector2f(0.f, 0.f), -1, 0);
			item.SetParent(-1);
			items.push_back(item);
			MoveItem(items.size() - 1);
			s->TryAddGroundItem(items.size() - 1);
		}
		{
			for (int i = 0; i < 3; i++)
			{
				Tree* t = new Tree(-1, id);
				AddStructure(t);
				t->SetPosition(sf::Vector2i(20 + i, 17));
			}
		}
		{
			for (int i = 0; i < 5; i++)
			{
				Boulder* t = new Boulder(-1, id);
				AddStructure(t);
				t->SetPosition(sf::Vector2i(25 + i, 17));
			}
		}
		return;
	}
	RandomHandler::SetNum(position);
	sf::Vector2i worldPos = position * CHUNK_SIZE;
	int seed = RandomHandler::seed;
	for (int x = 0; x < 32; x++)
	{
		for (int y = 0; y < 32; y++)
		{
			sf::Vector2i p(x, y);
			p += worldPos;
			float noise = RandomHandler::getNoise(p.x, p.y);
			if (noise > 0.65f && RandomHandler::GetNextNumber() % 5 == 0)
			{
				Tree* t = new Tree(-1, id);
				AddStructure(t);
				t->SetPosition(p);
			}
		}
	}
	RandomHandler::SetSeed(seed + 1);
	for (int x = 0; x < 32; x++)
	{
		for (int y = 0; y < 32; y++)
		{
			sf::Vector2i p(x, y);
			p += worldPos;
			float noise = RandomHandler::getNoise(p.x, p.y);
			if (StructureInPos(p) == -1 && noise > 0.65f && RandomHandler::GetNextNumber() % 9 == 0)
			{
				Boulder* t = new Boulder(-1, id);
				AddStructure(t);
				t->SetPosition(p);
			}
		}
	}
	RandomHandler::SetSeed(seed);
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
		Chunk* c = GetChunk(item->chunkID);
		for (uint i = 0; i < c->items.size(); i++)
		{
			if (c->items[i] == index)
			{
				c->items.erase(c->items.begin() + i);
				break;
			}
		}
	}
	if (item->parent != -1)
	{
		return;
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
bool Planet::StructureInArea(sf::Vector2i position, sf::Vector2i size)
{
	sf::Vector2i minChunkPos(
		floor((float)position.x / (float)CHUNK_SIZE),
		floor((float)position.y / (float)CHUNK_SIZE));
	sf::Vector2i maxChunkPos(
		floor((float)(position.x + size.x) / (float)CHUNK_SIZE),
		floor((float)(position.y + size.y) / (float)CHUNK_SIZE));
	// position -= sf::Vector2i(chunkPos.x * CHUNK_SIZE, chunkPos.y * CHUNK_SIZE);
	//need to also check the chunks left and up
	for (int x = minChunkPos.x - 1; x <= maxChunkPos.x; x++)
	{
		for (int y = minChunkPos.y - 1; y <= maxChunkPos.y; y++)
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
				sf::IntRect rect1(pos, s->tileSize);
				sf::IntRect rect2(position, size);
				if (RectIntersectsRect(rect1, rect2))
				{
					return true;
				}
			}
		}
	}
	return false;
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

void Planet::WorldUpdate(float dt)
{
	// for (uint i = 0; i < chunks.size(); i++)
	// {

	// 	chunks[i].Update(dt);
	// }
	for (uint i = 0; i < items.size(); i++)
	{
		if (items[i].parent != -1)
		{
			continue;
		}
		if (game->activePlanet == id && game->toolHandler->draggingItem == i)
		{
			continue;
		}
		items[i].Update(dt, &game->planets[id]);
	}
	for (uint i = 0; i < structuresToUpdate.size(); i++)
	{
		structures[structuresToUpdate[i]]->Update(dt);
	}
}

void Planet::AddStructure(Structure* s)
{
	std::vector<int> nonUpdateIds = { 2 };
	bool update = true;
	for (int i = 0; i < nonUpdateIds.size(); i++)
	{
		if (nonUpdateIds[i] == s->typeID)
		{
			update = false;
			break;
		}
	}
	if (emptyStructureSlots.size() > 0)
	{
		int index = emptyStructureSlots.back();
		if (update)
		{
			structuresToUpdate.push_back(index);
		}
		structures[index] = s;
		emptyStructureSlots.pop_back();
	}
	else
	{
		if (update)
		{
			structuresToUpdate.push_back(structures.size());
		}
		structures.push_back(s);
	}
}

void Planet::RemoveStructure(int index)
{
	Chunk* c = GetChunk(structures[index]->chunkID);
	for (int i = 0; i < c->structures.size(); i++)
	{
		if (c->structures[i] == index)
		{
			c->structures.erase(c->structures.begin() + i);
			break;
		}
	}
	delete structures[index];
	structures[index] = nullptr;
	emptyStructureSlots.push_back(index);
	for (int i = 0; i < structuresToUpdate.size(); i++)
	{
		if (structuresToUpdate[i] == index)
		{
			structuresToUpdate.erase(structuresToUpdate.begin() + i);
			break;
		}
	}
}

std::vector<int> Planet::StructuresInArea(sf::Vector2i position, sf::Vector2i size)
{
	std::vector<int> structs = {};
	sf::Vector2i minChunkPos(
		floor((float)position.x / (float)CHUNK_SIZE),
		floor((float)position.y / (float)CHUNK_SIZE));
	sf::Vector2i maxChunkPos(
		floor((float)(position.x + size.x) / (float)CHUNK_SIZE),
		floor((float)(position.y + size.y) / (float)CHUNK_SIZE));
	// position -= sf::Vector2i(chunkPos.x * CHUNK_SIZE, chunkPos.y * CHUNK_SIZE);
	//need to also check the chunks left and up
	for (int x = minChunkPos.x - 1; x <= maxChunkPos.x; x++)
	{
		for (int y = minChunkPos.y - 1; y <= maxChunkPos.y; y++)
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
				sf::IntRect rect1(pos, s->tileSize);
				sf::IntRect rect2(position, size);
				if (RectIntersectsRect(rect1, rect2))
				{
					structs.push_back(chunks[chunk].structures[i]);
				}
			}
		}
	}
	return structs;
}

bool Planet::DeductResources(int typeID, sf::Vector2i position)
{
	sf::Vector2i distance(50, 50);
	std::vector<int> structures = StructuresInArea(position - distance, 2 * distance);
	std::vector<int> silos = {};
	std::vector<float> dists = {};

	for (int i = 0; i < structures.size(); i++)
	{
		if (this->structures[structures[i]]->typeID == 1)
		{
			float x = position.x - this->structures[structures[i]]->position.x;
			float y = position.y - this->structures[structures[i]]->position.y;
			float dist = x * x + y * y;
			int index = dists.size();
			for (int j = 0; j < dists.size(); j++)
			{
				if (dists[j] > dist)
				{
					index = j;
					break;
				}
			}
			dists.insert(dists.begin() + index, dist);
			silos.insert(silos.begin() + index, structures[i]);
		}
	}
	std::vector<int> idsLeft = {};
	std::vector<int> idsCopy = {};
	std::vector<int> amountsLeft = {};
	std::vector<int> amountsCopy = {};

	auto cost = ResourceHandler::GetCost(typeID);
	for (int i = 1; i < cost.size(); i += 2)
	{
		idsLeft.push_back(cost[i]);
		idsCopy.push_back(cost[i]);
		amountsLeft.push_back(cost[i + 1]);
		amountsCopy.push_back(cost[i + 1]);
	}

	for (int i = 0; i < silos.size(); i++)
	{
		StorageSilo* s = dynamic_cast<StorageSilo*>(this->structures[silos[i]]);

		for (int k = 0; k < idsCopy.size(); k++)
		{
			for (int j = 0; j < s->itemIDs.size(); j++)
			{
				if (s->itemIDs[j] == idsCopy[k])
				{

					amountsCopy[k] -= s->itemQuantities[j];
					if (amountsCopy[k] <= 0)
					{
						amountsCopy.erase(amountsCopy.begin() + k);
						idsCopy.erase(idsCopy.begin() + k);
						k--;
						break;
					}
				}
			}
		}
	}

	if (idsCopy.size() != 0)
	{
		return false;
	}
	for (int i = 0; i < silos.size(); i++)
	{
		for (int k = 0; k < idsLeft.size(); k++)
		{
			StorageSilo* s = dynamic_cast<StorageSilo*>(this->structures[silos[i]]);
			for (int j = 0; j < s->itemIDs.size(); j++)
			{
				if (s->itemIDs[j] == idsLeft[k])
				{
					s->itemQuantities[j] -= amountsLeft[k];
					if (s->itemQuantities[j] <= 0)
					{
						amountsLeft[k] = -(s->itemQuantities[j]);
						s->itemQuantities.erase(s->itemQuantities.begin() + j);
						s->itemIDs.erase(s->itemIDs.begin() + j);
					}
					else
					{
						amountsLeft[k] = 0;
					}
					if (amountsLeft[k] <= 0)
					{
						amountsLeft.erase(amountsLeft.begin() + k);
						idsLeft.erase(idsLeft.begin() + k);
					}
				}
			}
		}
	}

	return true;
}

void Planet::RemoveStructuresInArea(sf::Vector2i position, sf::Vector2i size)
{
	std::vector<int> structures = StructuresInArea(position, size);
	for (int i = 0; i < structures.size(); i++)
	{
		RemoveStructure(structures[i]);
	}
}
