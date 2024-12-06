#include "Item.hpp"
#include "Main.hpp"
Item::Item(sf::Vector2f position)
{
	this->position = position;
	typeId = rand() % ResourceHandler::numItems;
	sf::Texture& t = ResourceHandler::outlineTextures[typeId];
	sprite.setTexture(t);
	sprite.setOrigin((sf::Vector2f)t.getSize() / 2.f);
	hitbox = new Hitbox(sf::Vector2f(0.f, 0.f), sf::Vector2f(1.f, 1.f));
	hitbox->AddShape(new HitboxRect(sf::Vector2f(0.f, 0.f), sf::Vector2f(ITEM_SIZE / 2.f, ITEM_SIZE / 2.f)));
	accurateHitbox = new Hitbox(sf::Vector2f(0.f, 0.f), sf::Vector2f(1.f, 1.f));

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
}

void Item::Update(float dt)
{
	hitbox->shapes[0]->currentPos = position;
	accurateHitbox->SetTransform(position, sf::Vector2f(1.f, 1.f));
}

void Item::Render()
{
	sprite.setPosition(position);
	accurateHitbox->Display({});

	window->draw(sprite);
}