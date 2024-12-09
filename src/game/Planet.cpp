#include "Planet.hpp"
#include "InputHandler.hpp"
#include "Main.hpp"
#include "binds.hpp"
#define sh SaveHandler

Planet::Planet(int id, bool load)
{
	this->id = id;
	if (id == 0)
	{
		backgroundColor = sf::Color(90, 128, 62);
	}
	draggingItem = -1;
	mouseStartDraggingPos = sf::Vector2f(0.f, 0.f);
	itemStartDraggingPos = sf::Vector2f(0.f, 0.f);
	chunks = {};
	camera = Camera();
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
			int chunkID = std::stoi(itemTable.GetValue("ChunkID", i));
			Item item = Item(pos, id, typeId);
			//TODO: DEAL WITH PARENT ATTRIBUTE
			for (uint i = 0; i < chunks.size(); i++)
			{
				if (chunks[i].id == chunkID)
				{
					chunks[i].items.push_back(item);
					break;
				}
			}
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
		int numItems = 10;
		chunks.push_back(Chunk(sf::Vector2i(0, 0), -1, this->id));
		for (uint i = 0; i < numItems; i++)
		{
			int size = 100;
			chunks[0].items.push_back(Item(
				sf::Vector2f(rand() % (size * 2) - size, rand() % (size * 2) - size),
				-1,
				rand() % ResourceHandler::numItems));
		}
	}
}

void Planet::Update(float dt)
{
	camera.Update(dt);
	if (draggingItem == -1)
	{
		for (int j = 0; j < chunks.size(); j++)
		{
			bool end = false;
			for (int i = chunks[j].items.size() - 1; i > -1; i--)
			{
				if (chunks[j].items[i].accurateHitbox->intersectsPoint(camera.WorldMousePos()))
				{

					if (InputHandler::pressed(binds::DragItem))
					{
						draggingItem = i;
						draggingChunk = j;
						mouseStartDraggingPos = camera.WorldMousePos();
						itemStartDraggingPos = chunks[j].items[i].position;
					}
					else if (!InputHandler::down(binds::DragItem))
					{
						chunks[j].items[i].selected = true;
					}
					end = true;
					break;
				}
			}
			if (end)
				break;
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
			chunks[draggingChunk].items[draggingItem].position = itemStartDraggingPos + offset;
		}
	}
	for (uint i = 0; i < chunks.size(); i++)
	{
		chunks[i].Update(dt);
	}
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
		chunks[i].Render();
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
	itemTable.headers = { "ItemID", "TypeID", "ChunkID", "PositionX", "PositionY", "Parent" };
	for (uint i = 0; i < chunks.size(); i++)
	{
		for (int j = 0; j < chunks[i].items.size(); j++)
		{
			itemTable.records.push_back({ std::to_string(chunks[i].items[j].id),
				std::to_string(chunks[i].items[j].typeId),
				std::to_string(chunks[i].id),
				std::to_string(chunks[i].items[j].position.x),
				std::to_string(chunks[i].items[j].position.y),
				"-1" });
		}
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