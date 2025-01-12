#include "Item.hpp"
#include "Main.hpp"
int CurrentItemID = 0;
Item::Item(sf::Vector2f position, int id, int typeID)
{
	chunkID = -1;
	if (id == -1)
	{
		this->id = CurrentItemID++;
	}
	else
	{
		this->id = id;
		if (this->id >= CurrentItemID)
		{
			CurrentItemID = this->id + 1;
		}
	}
	this->position = position;
	this->typeId = typeID;
	accurateHitbox = nullptr;
	ResourceHandler::itemAtlas->SetSprite(sprite, typeID);
	hitbox = new Hitbox(sf::Vector2f(0.f, 0.f), sf::Vector2f(1.f, 1.f));
	hitbox->AddShape(new HitboxRect(sf::Vector2f(0.f, 0.f), sf::Vector2f(ITEM_SIZE / 2.f, ITEM_SIZE / 2.f)));
	zindex = 1;
	moveDir = sf::Vector2f(0.f, 0.f);
}

void Item::Update(float dt, Planet* planet)
{
	hitbox->shapes[0]->currentPos = position;
	hitbox->SetTransform(position, sf::Vector2f(1.f, 1.f));
	if (accurateHitbox != nullptr)
		accurateHitbox->SetTransform(position, sf::Vector2f(1.f, 1.f));
	sf::Vector2i tilePos = planet->tilePos(position);
	int i = planet->StructureInPos(tilePos);
	if (i == -1)
	{
		moveDir = sf::Vector2f(0.f, 0.f);
		return;
	}
	Structure* s = planet->structures[i];
	int index;
	for (int i = 0; i < planet->items.size(); i++)
	{
		if (planet->items[i].id == id)
		{
			index = i;
			break;
		}
	}
	if (!s->blocksItems)
	{
		s->TryAddGroundItem(index);
	}
	else
	{
		sf::Vector2f worldTilePos(tilePos.x * TILE_SIZE.x, tilePos.y * TILE_SIZE.y);
		sf::Vector2f pos = position - worldTilePos;
		pos.x /= TILE_SIZE.x;
		pos.y /= TILE_SIZE.y;
		float distx = (pos.x < 0.5f) ? pos.x : 1 - pos.x;
		float disty = (pos.y < 0.5f) ? pos.y : 1 - pos.y;
		if (moveDir == sf::Vector2f(0.f, 0.f))
		{
			if (distx < disty)
			{
				moveDir = sf::Vector2f((pos.x < 0.5f) ? -1 : 1, 0.f);
			}
			else
			{
				moveDir = sf::Vector2f(0.f, (pos.y < 0.5f) ? -1 : 1);
			}
			moveDir.x *= 1.1f;
			moveDir.y *= 1.1f;
		}

		position.x = (tilePos.x + (moveDir.x + 1) / 2.f) * TILE_SIZE.x;
		position.y = (tilePos.y + (moveDir.y + 1) / 2.f) * TILE_SIZE.y;
	}
}

void Item::Render(Planet* planet)
{
	if (parent == -1)
	{
		zindex = 100;
	}
	else
	{
		zindex = 1;
	}
	sprite.setPosition(position);
	planet->renderObjects.push_back(RenderObject {
		&sprite,
		zindex });
}

void Item::SetParent(int index)
{
	parent = index;
	if (parent == -1 && accurateHitbox == nullptr)
	{
		accurateHitbox = new Hitbox(sf::Vector2f(0.f, 0.f), sf::Vector2f(1.f, 1.f));
		auto image = ResourceHandler::itemTextures[typeId].copyToImage();
		for (uint i = 0; i < 16; i++)
		{
			int startPos = -1;
			for (int j = 0; j < 16; j++)
			{
				sf::Color pixel = image.getPixel(j, i);
				if (pixel.a == 0)
				{
					if (startPos != -1)
					{
						HitboxRect* rect = new HitboxRect(sf::Vector2f((startPos + j) / 2.f, i + 0.5f), sf::Vector2f((j - startPos) / 2.f, .5f));
						rect->position -= sf::Vector2f(ITEM_SIZE / 2.f, ITEM_SIZE / 2.f);
						accurateHitbox->AddShape(rect);
						startPos = -1;
					}
				}
				else
				{
					if (startPos == -1)
					{
						startPos = j;
					}
				}
			}
			if (startPos != -1)
			{
				HitboxRect* rect = new HitboxRect(sf::Vector2f((startPos + 17) / 2.f, i + 0.5f), sf::Vector2f((17 - startPos) / 2.f, .5f));
				rect->position -= sf::Vector2f(ITEM_SIZE / 2.f, ITEM_SIZE / 2.f);
				accurateHitbox->AddShape(rect);
			}
		}
	}
}

sf::Vector2i Item::GetTilePos()
{
	sf::Vector2i worldTilePos(floor(position.x / TILE_SIZE.x), floor(position.y / TILE_SIZE.y));
	sf::Vector2i chunkPos(floor((float)worldTilePos.x / CHUNK_SIZE), floor((float)worldTilePos.y / CHUNK_SIZE));
	return worldTilePos - chunkPos * CHUNK_SIZE;
}

void Item::SetType(int typeID)
{
	this->typeId = typeID;
	ResourceHandler::itemAtlas->SetSprite(this->sprite, typeID);
}