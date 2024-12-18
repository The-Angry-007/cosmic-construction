#include "ToolHandler.hpp"
#include "Main.hpp"
#include "binds.hpp"

ToolHandler::ToolHandler()
{
	selectedTool = 0;

	selectedObj = guihandler.guis[5]->GUIObjects[3 * guihandler.numTools];
	selectedObj->position = guihandler.toolPoses[selectedTool];
	bgObjs = {};
	for (int i = 0; i < guihandler.numTools; i++)
	{
		bgObjs.push_back(dynamic_cast<GUIPanel*>(guihandler.guis[5]->GUIObjects[guihandler.numTools + i * 2]));
		bgObjs[i]->blocksMouseInput = true;
	}
	hoveringItem = -1;
	draggingItem = -1;
	placeDir = 0;
	mouseStartDraggingPos = sf::Vector2f(0.f, 0.f);
	itemStartDraggingPos = sf::Vector2f(0.f, 0.f);
}

void ToolHandler::Update(float dt, Planet* p)
{
	for (int i = 0; i < bgObjs.size(); i++)
	{
		if (bgObjs[i]->isClicked())
		{
			selectedTool = i;
			InputHandler::RemoveMbPressed(sf::Mouse::Button::Left);
			InputHandler::RemoveMbDown(sf::Mouse::Button::Left);
		}
		if (bgObjs[i]->isBlockingMouse())
		{
			InputHandler::mouseIsBlocked = true;
		}
	}
	if (InputHandler::pressed(binds::Tool1))
	{
		selectedTool = 0;
	}
	if (InputHandler::pressed(binds::Tool2))
	{
		selectedTool = 1;
	}
	selectedObj->position = guihandler.toolPoses[selectedTool];
	if (InputHandler::pressed(binds::RotateStructure))
	{
		placeDir = (placeDir + 1) % 4;
	}
	if (selectedTool == 0)
	{
		if (InputHandler::down(binds::UseTool))
		{
			sf::Vector2f mousePos = p->camera.WorldMousePos();
			sf::Vector2i tilePos(floor(mousePos.x / TILE_SIZE.x), floor(mousePos.y / TILE_SIZE.y));

			if (p->StructureInPos(tilePos) == -1)
			{
				Conveyor* s = new Conveyor(-1, p->id, placeDir);
				p->structures.push_back(s);
				s->SetPosition(tilePos);
			}
		}
	}
	else if (selectedTool == 1)
	{
		if (hoveringItem != -1)
		{
			ResourceHandler::itemAtlas->SetSprite(p->items[hoveringItem].sprite, p->items[hoveringItem].typeId);
		}
		if (draggingItem == -1)
		{
			bool end = false;
			for (int i = p->items.size() - 1; i > -1; i--)
			{
				if (p->items[i].parent != -1)
				{
					continue;
				}
				if (p->items[i].accurateHitbox->intersectsPoint(p->camera.WorldMousePos()) && !InputHandler::mouseIsBlocked)
				{

					if (InputHandler::pressed(binds::UseTool))
					{
						draggingItem = i;
						mouseStartDraggingPos = p->camera.WorldMousePos();
						itemStartDraggingPos = p->items[i].position;
					}
					else if (!InputHandler::down(binds::UseTool))
					{
						hoveringItem = i;
						ResourceHandler::itemAtlas->SetSprite(p->items[hoveringItem].sprite, p->items[hoveringItem].typeId + ResourceHandler::numItems);
					}
					end = true;
					break;
				}
			}
		}
		else
		{
			if (!InputHandler::down(binds::UseTool))
			{
				draggingItem = -1;
			}
			else
			{
				sf::Vector2f offset = p->camera.WorldMousePos() - mouseStartDraggingPos;
				p->items[draggingItem].position = itemStartDraggingPos + offset;
				p->MoveItem(draggingItem);
			}
		}
	}
}
