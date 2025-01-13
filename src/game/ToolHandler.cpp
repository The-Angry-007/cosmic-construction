#include "ToolHandler.hpp"
#include "Main.hpp"
#include "binds.hpp"
#include "utils.hpp"

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
	insufficientLabel = nullptr;
	selectedImages = {};
	for (int i = 0; i < 4; i++)
	{
		selectedImages.push_back(new GUIImage(sf::Vector2f(0.5f, 0.5f), sf::Vector2f(0.5f, 0.5f), "resources\\images\\selection" + std::to_string(i + 1) + ".png"));
		selectedImages[i]->keepAspectRatio = true;
	}
}

void ToolHandler::Update(float dt, Planet* p)
{
	if (insufficientLabel != nullptr)
	{
		float time = 1.5f;
		if (insufficientTimer.getElapsedTime().asSeconds() > time)
		{
			guihandler.guis[5]->RemoveObject(guihandler.guis[5]->GetIndex(insufficientLabel));
			insufficientLabel = nullptr;
		}
		else
		{
			float prog = insufficientTimer.getElapsedTime().asSeconds() / time;
			prog = 1 - prog;
			insufficientLabel->SetColor(sf::Color(255, 0, 0, Lerp(0, 255, prog)));
			insufficientLabel->position = { 0.5f, 0.3f + prog * 0.2f };
		}
	}

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
	if (InputHandler::pressed(binds::Tool3))
	{
		selectedTool = 2;
	}
	selectedObj->position = guihandler.toolPoses[selectedTool];
	if (InputHandler::pressed(binds::RotateStructure))
	{
		placeDir = (placeDir + 1) % 4;
	}
	sf::Vector2f mousePos = p->camera.WorldMousePos();
	sf::Vector2i tilePos(floor(mousePos.x / TILE_SIZE.x), floor(mousePos.y / TILE_SIZE.y));
	//draw selections
	for (int i = 0; i < 4; i++)
	{
		int j = guihandler.guis[5]->GetIndex(selectedImages[i]);
		selectedImages[i]->sprite.setColor(sf::Color::White);
		if (j != -1)
		{
			guihandler.guis[5]->RemoveObject(j);
		}
	}
	int index = p->StructureInPos(tilePos);
	if (index != -1)
	{
		Structure* s = p->structures[index];
		sf::Vector2f coords = (sf::Vector2f)(s->position + p->GetChunk(s->chunkID)->position * CHUNK_SIZE);
		sf::Vector2f tileSize = (sf::Vector2f)s->tileSize - sf::Vector2f(1.f, 1.f);
		sf::Vector2f tl = p->camera.tileToGUIPos({ 0.f, 0.f });
		sf::Vector2f br = p->camera.tileToGUIPos({ 1.f, 1.f });
		sf::Vector2f size = (br - tl) / 2.f;
		selectedImages[0]->position = p->camera.tileToGUIPos(coords + sf::Vector2f(0.f, 0.f) + sf::Vector2f(0.5f, 0.5f));
		selectedImages[0]->size = size;
		selectedImages[1]->position = p->camera.tileToGUIPos(coords + sf::Vector2f(tileSize.x, 0.f) + sf::Vector2f(0.5f, 0.5f));
		selectedImages[1]->size = size;
		selectedImages[2]->position = p->camera.tileToGUIPos(coords + tileSize + sf::Vector2f(0.5f, 0.5f));
		selectedImages[2]->size = size;
		selectedImages[3]->position = p->camera.tileToGUIPos(coords + sf::Vector2f(0.f, tileSize.y) + sf::Vector2f(0.5f, 0.5f));
		selectedImages[3]->size = size;

		guihandler.guis[5]->AddObject(selectedImages[0]);
		guihandler.guis[5]->AddObject(selectedImages[1]);
		guihandler.guis[5]->AddObject(selectedImages[2]);
		guihandler.guis[5]->AddObject(selectedImages[3]);
	}
	if (selectedTool == 0)
	{

		if (previewStructure != nullptr)
		{
			delete previewStructure;
			previewStructure = nullptr;
		}

		if (placeType == 0)
		{

			Conveyor* c = new Conveyor(0, game->activePlanet, placeDir);
			c->SetVisualPosition(tilePos);

			previewStructure = c;

			if (InputHandler::down(binds::UseTool))
			{
				if (p->StructureInPos(tilePos) == -1)
				{
					if (p->DeductResources(0, tilePos))
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
						p->AddStructure(s);
						s->SetPosition(tilePos);
					}
					else
					{
						ShowInsufficient();
					}
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
			sf::Vector2i pos = tilePos - sf::Vector2i(1, 1);

			StorageSilo* s = new StorageSilo(0, game->activePlanet);
			s->SetVisualPosition(pos);

			previewStructure = s;

			if (InputHandler::pressed(binds::UseTool))
			{
				if (!p->StructureInArea(pos, ResourceHandler::structureSizes[1]))
				{
					if (p->DeductResources(1, pos))
					{
						StorageSilo* s = new StorageSilo(-1, p->id);
						p->AddStructure(s);

						s->SetPosition(pos);
					}
					else
					{
						ShowInsufficient();
					}
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
			// p->items[hoveringItem].SetParent(-1);
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
					p->items[hoveringItem].zindex = 100;

					ResourceHandler::itemAtlas->SetSprite(p->items[hoveringItem].sprite, p->items[hoveringItem].typeId + ResourceHandler::numItems);
				}
			}
		}
		else
		{
			if (!InputHandler::down(binds::UseTool))
			{
				draggingItem = -1;
				hoveringItem = -1;
			}
			else
			{
				sf::Vector2f offset = p->camera.WorldMousePos() - mouseStartDraggingPos;
				p->items[draggingItem].position = itemStartDraggingPos + offset;
				p->items[draggingItem].moveDir = sf::Vector2f(0.f, 0.f);
				p->MoveItem(draggingItem);
			}
		}
		if (InputHandler::pressed(binds::UseTool) && draggingItem == -1)
		{
			int index = p->StructureInPos(tilePos);
			if (index != -1)
			{
				Structure* s = p->structures[index];
				if (s->typeID == 2)
				{
					Tree* t = dynamic_cast<Tree*>(s);
					t->health--;
					if (t->health <= 0)
					{
						t->Destroy();
						p->RemoveStructure(index);
					}
				}
			}
		}
	}
	else if (selectedTool == 2)
	{
		for (int i = 0; i < 4; i++)
		{
			selectedImages[i]->sprite.setColor(sf::Color::Red);
		}
		if (InputHandler::down(binds::UseTool) && index != -1)
		{
			if (p->structures[index]->placedByPlayer)
			{
				int type = p->structures[index]->typeID;
				auto cost = ResourceHandler::GetCost(type);
				sf::Vector2f pos = (sf::Vector2f)(p->structures[index]->position + p->GetChunk(p->structures[index]->chunkID)->position * CHUNK_SIZE);
				pos += (sf::Vector2f)(p->structures[index]->tileSize) / 2.f;
				pos.x *= TILE_SIZE.x;
				pos.y *= TILE_SIZE.y;
				for (int i = 1; i < cost.size(); i += 2)
				{
					for (int j = 0; j < cost[i + 1]; j++)
					{
						sf::Vector2f randPos(rand() % 1000 - 500, rand() % 1000 - 500);
						randPos.x *= (p->structures[index]->tileSize.x / 2.f);
						randPos.y *= (p->structures[index]->tileSize.y / 2.f);
						randPos /= 500.f;
						randPos.x *= TILE_SIZE.x;
						randPos.y *= TILE_SIZE.y;
						// Item item = Item(sf::Vector2f(rand() % 1000, rand() % 1000) / 1000.f + pos, -1, cost[i]);
						p->items.push_back(Item(pos + randPos, -1, cost[i]));
						p->items.back().SetParent(-1);
						p->MoveItem(p->items.size() - 1);
					}
				}
				p->RemoveStructure(index);
				std::cout << p->items.size() << std::endl;
			}
		}
	}
}

void ToolHandler::ShowInsufficient()
{
	if (insufficientLabel == nullptr)
	{
		insufficientLabel = new GUILabel(sf::Vector2f(0.5f, 0.5f), sf::Vector2f(0.3f, 0.1f), "Insufficient Resources");
		insufficientLabel->SetColor(sf::Color::Red);
		guihandler.guis[5]->AddObject(insufficientLabel);
	}
	insufficientTimer.restart();
}