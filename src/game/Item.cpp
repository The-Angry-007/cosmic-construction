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
	sf::Texture& t = ResourceHandler::itemTextures[typeId];
	sprite.setTexture(t);
	sprite.setOrigin((sf::Vector2f)t.getSize() / 2.f);
	hitbox = new Hitbox(sf::Vector2f(0.f, 0.f), sf::Vector2f(1.f, 1.f));
	hitbox->AddShape(new HitboxRect(sf::Vector2f(0.f, 0.f), sf::Vector2f(ITEM_SIZE / 2.f, ITEM_SIZE / 2.f)));
	accurateHitbox = new Hitbox(sf::Vector2f(0.f, 0.f), sf::Vector2f(1.f, 1.f));
	selected = false;
	auto image = t.copyToImage();
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
	selectedSprite = false;
}

void Item::Update(float dt)
{
	hitbox->shapes[0]->currentPos = position;
	accurateHitbox->SetTransform(position, sf::Vector2f(1.f, 1.f));

	if (selected && !selectedSprite)
	{
		sprite.setTexture(ResourceHandler::itemOutlines[typeId], true);
		sprite.setOrigin(ITEM_SIZE / 2 + 1, ITEM_SIZE / 2 + 1);
		selectedSprite = true;
	}
	else if (!selected && selectedSprite)
	{
		selectedSprite = false;
		sprite.setTexture(ResourceHandler::itemTextures[typeId], true);
		sprite.setOrigin(ITEM_SIZE / 2, ITEM_SIZE / 2);
	}

	selected = false;
}

void Item::Render()
{
	sprite.setPosition(position);
	window->draw(sprite);
}