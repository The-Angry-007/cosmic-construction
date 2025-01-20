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
		bgObjs.push_back(dynamic_cast<GUIPanel*>(guihandler.guis[5]->GUIObjects[guihandler.numTools + i * 2]));
		bgObjs[i]->blocksMouseInput = true;
	}
	draggingItems = {};
	hoveringItem = nullptr;
	placeDir = 0;
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
	draggingStructure = -1;
	prevmousepos = sf::Vector2f(0.f, 0.f);
	tallyObjs = {};
}
ToolHandler::~ToolHandler()
{
	for (int i = 0; i < 4; i++)
	{
		int j = guihandler.guis[5]->GetIndex(selectedImages[i]);
		selectedImages[i]->sprite.setColor(sf::Color::White);
		if (j != -1)
		{
			guihandler.guis[5]->RemoveObject(j);
		}
	}
	if (insufficientLabel != nullptr)
	{
		guihandler.guis[5]->RemoveObject(guihandler.guis[5]->GetIndex(insufficientLabel));
	}
	ClearTally();
}
void ToolHandler::Update(float dt, Planet* p)
{
	delete hoveringItem;
	hoveringItem = nullptr;
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
	//CHANGING CURRENT TOOL
	for (int i = 0; i < bgObjs.size(); i++)
	{
		if (bgObjs[i]->isClicked())
		{
			if (i == 0 && selectedTool == 0)
			{
				game->inMenu = true;
				guihandler.OpenGUI(7);
			}
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
	//SOME USEFUL VARIABLES
	sf::Vector2f mousePos = p->camera.WorldMousePos();
	sf::Vector2i tilePos(floor(mousePos.x / TILE_SIZE.x), floor(mousePos.y / TILE_SIZE.y));

	int index = p->StructureInPos(tilePos);

	// #
	// #
	// #SELECTED TOOL 0
	// #
	// #

	if (selectedTool == 0)
	{
		if (previewStructure != nullptr)
		{
			delete previewStructure;
			previewStructure = nullptr;
		}
		ReloadTally(tilePos);
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
		else
		{
			sf::Vector2f pos1(mousePos.x / TILE_SIZE.x, mousePos.y / TILE_SIZE.y);
			pos1 -= (sf::Vector2f)(ResourceHandler::structureSizes[placeType] - sf::Vector2i(1, 1)) / 2.f;
			sf::Vector2i pos(floor(pos1.x), floor(pos1.y));

			sf::Vector2i size = ResourceHandler::structureSizes[placeType];
			// sf::Vector2i pos = tilePos;
			// sf::Vector2i size = ResourceHandler::structureSizes[placeType];
			// pos -= size;

			// StorageSilo* s = new StorageSilo(0, game->activePlanet);
			Structure* s = CreateStructure(placeType);
			s->SetVisualPosition(pos);

			previewStructure = s;

			if (InputHandler::pressed(binds::UseTool))
			{
				if (!p->StructureInArea(pos, size))
				{
					if (p->DeductResources(placeType, pos))
					{
						Structure* s2 = CreateStructure(placeType);
						s2->SetID(-1);
						p->AddStructure(s2);

						s2->SetPosition(pos);
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
	// #
	// #
	// #SELECTED TOOL 1
	// #
	// #

	else if (selectedTool == 1)
	{
		if (draggingStructure != -1)
		{
			if (prevmousepos == sf::Vector2f(0.f, 0.f))
			{
				prevmousepos = mousePos;
			}
			if (p->structures[draggingStructure] == nullptr)
			{
				draggingStructure = -1;
			}
			if (!InputHandler::down(binds::UseTool))
			{
				sf::Vector2f offset = structureStartDraggingPos - mousePos;
				if (offset.x * offset.x + offset.y * offset.y < 9.f)
				{
					p->structures[draggingStructure]->Interact();
				}
				draggingStructure = -1;
				prevmousepos = sf::Vector2f(0.f, 0.f);
			}
			else
			{

				sf::Vector2i originalTilePos(floor(prevmousepos.x / TILE_SIZE.x), floor(prevmousepos.y / TILE_SIZE.y));
				sf::Vector2i newTilePos(floor(mousePos.x / TILE_SIZE.x), floor(mousePos.y / TILE_SIZE.y));
				if (newTilePos != originalTilePos && p->structures[draggingStructure]->placedByPlayer)
				{
					sf::Vector2i diff = newTilePos - originalTilePos;
					Structure* s = p->structures[draggingStructure];
					sf::Vector2i newPos = diff + s->position + p->GetChunk(s->chunkID)->position * CHUNK_SIZE;
					auto structs = p->StructuresInArea(newPos, s->tileSize);
					if (structs.size() == 0 || structs.size() == 1 && structs[0] == draggingStructure)
					{
						s->SetPosition(newPos);
						prevmousepos = mousePos;
					}
				}
			}
		}
		else if (draggingItems.size() == 0 || InputHandler::keyDown(sf::Keyboard::Key::LShift))
		{
			bool end = false;
			std::vector<int> touchingItems = {};
			for (int i = 0; i < p->items.size(); i++)
			{
				if (p->items[i].parent != -1)
				{
					continue;
				}
				bool dragging = false;
				for (int j = 0; j < draggingItems.size(); j++)
				{
					if (draggingItems[j] == i)
					{
						dragging = true;
						break;
					}
				}
				if (dragging)
					continue;
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
					draggingItems = { i };
				}
				else if (!InputHandler::down(binds::UseTool))
				{

					hoveringItem = new Item(p->items[i].position, -2, p->items[i].typeId);
					hoveringItem->zindex = 100;
					ResourceHandler::itemAtlas->SetSprite(hoveringItem->sprite, hoveringItem->typeId + ResourceHandler::numItems);
					hoveringItem->Render(p);
				}
				else if (InputHandler::down(binds::UseTool) && InputHandler::keyDown(sf::Keyboard::Key::LShift))
				{
					draggingItems.push_back(i);
				}
			}
		}

		if (!InputHandler::down(binds::UseTool))
		{
			if (index != -1 && draggingItems.size() > 1)
			{
				for (int i = 0; i < draggingItems.size(); i++)
				{
					sf::Vector2f pos = (sf::Vector2f)tilePos;
					pos += sf::Vector2f(rand() % 1000, rand() % 1000) / 1000.f;
					pos.x *= TILE_SIZE.x;
					pos.y *= TILE_SIZE.y;
					p->items[draggingItems[i]].position = pos;
				}
			}
			draggingItems = {};
		}
		else
		{
			sf::Vector2f offset = p->camera.WorldMousePos();
			for (int i = 0; i < draggingItems.size(); i++)
			{
				sf::Vector2f stackOffset(0.f, 1.f * i);
				p->items[draggingItems[i]].position = offset - stackOffset;
				p->items[draggingItems[i]].moveDir = sf::Vector2f(0.f, 0.f);
				p->MoveItem(draggingItems[i]);
			}
		}
		if (draggingItems.size() == 0 && hoveringItem == nullptr)
		{
			if (InputHandler::pressed(binds::UseTool) && index != -1)
			{
				structureStartDraggingPos = mousePos;
				draggingStructure = index;
			}
			else if (InputHandler::pressed(binds::RotateStructure) && index != -1)
			{
				p->structures[index]->SetDirection((p->structures[index]->direction + 1) % 4);
			}
		}
	}

	// #
	// #
	// #SELECTED TOOL 2
	// #
	// #
	else if (selectedTool == 2)
	{

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
				p->structures[index]->Destroy();
				p->RemoveStructure(index);
			}
		}
		if (InputHandler::pressed(binds::UseTool))
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
				else if (s->typeID == 5)
				{
					Boulder* t = dynamic_cast<Boulder*>(s);
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
	index = p->StructureInPos(tilePos);
	if (index != -1 && ((selectedTool == 1 && hoveringItem == nullptr && draggingItems.size() == 0) || selectedTool == 2))
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

		guihandler.guis[5]->InsertObject(selectedImages[0], 0);
		guihandler.guis[5]->InsertObject(selectedImages[1], 0);
		guihandler.guis[5]->InsertObject(selectedImages[2], 0);
		guihandler.guis[5]->InsertObject(selectedImages[3], 0);
	}
	if (selectedTool == 2)
	{
		for (int i = 0; i < 4; i++)
		{
			selectedImages[i]->sprite.setColor(sf::Color::Red);
		}
	}
	if (selectedTool != 0)
	{
		ClearTally();
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

Structure* ToolHandler::CreateStructure(int type)
{
	if (type == 1)
	{
		return new StorageSilo(-2, game->activePlanet, placeDir);
	}
	else if (type == 3)
	{
		return new TreeChopper(-2, game->activePlanet, placeDir);
	}
	else if (type == 4)
	{
		return new SaplingPlanter(-2, game->activePlanet, placeDir);
	}
	else if (type == 6)
	{
		return new Drill(-2, game->activePlanet, placeDir);
	}
	else
	{
		return nullptr;
	}
}

void ToolHandler::Render()
{
	//remove selections
	for (int i = 0; i < 4; i++)
	{
		int j = guihandler.guis[5]->GetIndex(selectedImages[i]);
		selectedImages[i]->sprite.setColor(sf::Color::White);
		if (j != -1)
		{
			guihandler.guis[5]->RemoveObject(j);
		}
	}
}

void ToolHandler::ReloadTally(sf::Vector2i tilePos)
{
	auto cost = ResourceHandler::GetCost(placeType);
	std::vector<int> types = {};
	for (int i = 1; i < cost.size(); i += 2)
	{
		types.push_back(cost[i]);
	}
	Planet& p = game->planets[game->activePlanet];
	std::vector<int> tally = p.TallyResources(tilePos, types);
	GUI* g = guihandler.guis[5];
	for (int i = 0; i < tallyObjs.size(); i++)
	{
		g->RemoveObject(g->GetIndex(tallyObjs[i]));
		delete tallyObjs[i];
	}
	tallyObjs = {};
	float width = 0.03f;
	float totalWidth = (tally.size() * 2.f) * width * 2.f;
	float y = 0.75f;
	sf::Vector2f startPos(0.5f - totalWidth / 2.f, y);
	sf::Vector2f endPos(0.5f + totalWidth / 2.f, y);
	int N = tally.size() * 2;
	for (int i = 0; i < tally.size(); i++)
	{
		int index = 2 * i + 1;

		sf::Vector2f pos1 = Lerp(startPos, endPos, (index * 2.f - 1.f) / (N * 2.f));
		sf::Vector2f pos2 = Lerp(startPos, endPos, ((index + 1) * 2.f - 1.f) / (N * 2.f));
		std::string str = std::to_string(tally[i]);
		str += " / ";
		str += std::to_string(cost[i * 2 + 2]);
		GUILabel* l = new GUILabel(pos2, sf::Vector2f(width, width), str);
		GUIItem* item = new GUIItem(pos1, sf::Vector2f(width, width), cost[i * 2 + 1], 0);
		tallyObjs.push_back(l);
		tallyObjs.push_back(item);
		g->AddObject(l);
		g->AddObject(item);
	}
}

void ToolHandler::ClearTally()
{
	for (int i = 0; i < tallyObjs.size(); i++)
	{
		guihandler.guis[5]->RemoveObject(guihandler.guis[5]->GetIndex(tallyObjs[i]));
		delete tallyObjs[i];
	}
	tallyObjs = {};
}