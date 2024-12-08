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
	else
	{
		backgroundColor = sf::Color(176, 98, 49);
	}
	items = {};
	draggingItem = -1;
	mouseStartDraggingPos = sf::Vector2f(0.f, 0.f);
	itemStartDraggingPos = sf::Vector2f(0.f, 0.f);
	camera = Camera();
	if (load)
	{
		std::string path = sh::workingDir + "\\planets\\" + std::to_string(id) + "\\";
		//loading items
		std::string itemPath = path + "items.txt";
		Table itemTable = Table();
		itemTable.FromString(SaveHandler::ReadData(itemPath));
		for (uint i = 0; i < itemTable.records.size(); i++)
		{
			sf::Vector2f pos(0, 0);
			pos.x = std::stof(itemTable.GetValue("PositionX", i));
			pos.y = std::stof(itemTable.GetValue("PositionY", i));
			int id = std::stoi(itemTable.GetValue("ItemID", i));
			int typeId = std::stoi(itemTable.GetValue("TypeID", i));

			Item item = Item(pos, id, typeId);
			//TODO: DEAL WITH PARENT ATTRIBUTE
			items.push_back(item);
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
		for (uint i = 0; i < numItems; i++)
		{
			int size = 100;
			items.push_back(Item(
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
					items[i].selected = true;
				}
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
		}
	}
	for (uint i = 0; i < items.size(); i++)
	{
		items[i].Update(dt);
	}
}

void Planet::Render()
{
	sf::FloatRect camRect = camera.toFloatRect();
	sf::RectangleShape rect(sf::Vector2f(camRect.width, camRect.height));
	rect.setPosition(camRect.left, camRect.top);
	rect.setFillColor(backgroundColor);
	window->draw(rect);
	for (uint i = 0; i < items.size(); i++)
	{
		items[i].Render();
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
	for (uint i = 0; i < items.size(); i++)
	{
		itemTable.records.push_back({ std::to_string(i),
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
}