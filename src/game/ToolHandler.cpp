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
		bgObjs.push_back(dynamic_cast<GUIImage*>(guihandler.guis[5]->GUIObjects[guihandler.numTools + i * 2 + 1]));
		bgObjs[i]->blocksMouseInput = true;
	}
	hoveringItem = -1;
	draggingItem = -1;
	placeDir = 0;
	mouseStartDraggingPos = sf::Vector2f(0.f, 0.f);
	itemStartDraggingPos = sf::Vector2f(0.f, 0.f);
	lastPlacedStructure = -1;
	placeType = 0;
	prevTilePos = sf::Vector2i(-10000, -10000);
	previewStructure = nullptr;
}

void ToolHandler::Update(float dt, Planet* p)
{
	if (InputHandler::pressed(binds::Build))
	{
		if (guihandler.activeGui == 7)
		{
			guihandler.GoBack();
			game->inMenu = false;
		}
		else
		{
			game->inMenu = true;

			guihandler.OpenGUI(7);
		}
	}
	if (game->inMenu)
	{
		return;
	}
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

		if (previewStructure != nullptr)
		{
			delete previewStructure;
			previewStructure = nullptr;
		}
		sf::Vector2f mousePos = p->camera.WorldMousePos();
		sf::Vector2i tilePos(floor(mousePos.x / TILE_SIZE.x), floor(mousePos.y / TILE_SIZE.y));
		if (placeType == 0)
		{

			Conveyor* c = new Conveyor(0, game->activePlanet, placeDir);
			c->SetVisualPosition(tilePos);

			previewStructure = c;

			if (InputHandler::down(binds::UseTool))
			{
				if (p->StructureInPos(tilePos) == -1)
				{
					int direction = placeDir;
					if (lastPlacedStructure != -1)
					{
						int dir = 0;
						sf::Vector2i offset = tilePos;
						sf::Vector2i prevpos = p->structures[lastPlacedStructure]->position + p->GetChunk(p->structures[lastPlacedStructure]->chunkID)->position * CHUNK_SIZE;
						offset -= prevpos;
						for (int i = 0; i < 4; i++)
						{
							if (CONVEYOR_OFFSETS[i] == offset)
							{
								dir = i;
							}
						}
						direction = dir;

						dynamic_cast<Conveyor*>(p->structures[lastPlacedStructure])->SetDirection(direction);
					}
					else
					{
						if (prevTilePos.x != -10000)
						{
							sf::Vector2i offset = tilePos;
							offset -= prevTilePos;
							int dir = 0;
							for (int i = 0; i < 4; i++)
							{
								if (CONVEYOR_OFFSETS[i] == offset)
								{
									dir = i;
								}
							}
							direction = dir;
						}
					}
					Conveyor* s = new Conveyor(-1, p->id, direction);
					lastPlacedStructure = p->structures.size();
					p->structures.push_back(s);
					s->SetPosition(tilePos);
				}
				else
				{
					if (lastPlacedStructure != -1)
					{
						if (prevTilePos != tilePos && prevTilePos.x != -10000)
						{
							sf::Vector2i offset = tilePos;
							offset -= prevTilePos;
							int dir = 0;
							for (int i = 0; i < 4; i++)
							{
								if (CONVEYOR_OFFSETS[i] == offset)
								{
									dir = i;
								}
							}
							dynamic_cast<Conveyor*>(p->structures[lastPlacedStructure])->SetDirection(dir);
						}
					}
					if (p->structures[p->StructureInPos(tilePos)]->typeID == 0)
					{
						lastPlacedStructure = p->StructureInPos(tilePos);
					}
				}
				prevTilePos = tilePos;
			}
			else
			{
				lastPlacedStructure = -1;
				prevTilePos = sf::Vector2i(-10000, -10000);
			}
		}
		else if (placeType == 1)
		{
			StorageSilo* s = new StorageSilo(0, game->activePlanet);
			s->SetVisualPosition(tilePos);

			previewStructure = s;

			if (InputHandler::pressed(binds::UseTool))
			{
				if (!p->StructureInArea(tilePos, ResourceHandler::structureSizes[1]))
				{
					StorageSilo* s = new StorageSilo(-1, p->id);
					p->structures.push_back(s);

					s->SetPosition(tilePos);
				}
			}
		}
		if (previewStructure != nullptr && !InputHandler::mouseIsBlocked && !game->inMenu)
		{
			previewStructure->RenderPreview();
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
			std::vector<int> touchingItems = {};
			for (int i = 0; i < p->items.size(); i++)
			{
				if (p->items[i].parent != -1)
				{
					continue;
				}
				if (p->items[i].accurateHitbox->intersectsPoint(p->camera.WorldMousePos()) && !InputHandler::mouseIsBlocked)
				{
					touchingItems.push_back(i);
				}
			}
			if (touchingItems.size() > 0)
			{
				int lowestYIndex = 0;
				for (int i = 0; i < touchingItems.size(); i++)
				{
					if (p->items[touchingItems[i]].position.y > p->items[touchingItems[lowestYIndex]].position.y)
					{
						lowestYIndex = i;
					}
					else if (p->items[touchingItems[i]].position.y == p->items[touchingItems[lowestYIndex]].position.y)
					{
						if (p->items[touchingItems[i]].position.x > p->items[touchingItems[lowestYIndex]].position.x)
						{
							lowestYIndex = i;
						}
					}
				}
				int i = touchingItems[lowestYIndex];
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
				p->items[draggingItem].moveDir = sf::Vector2f(0.f, 0.f);
				p->MoveItem(draggingItem);
			}
		}
	}
}
