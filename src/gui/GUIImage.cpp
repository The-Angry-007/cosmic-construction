#include "GUIImage.hpp"
#include "Main.hpp"
GUIImage::GUIImage(sf::Vector2f position, sf::Vector2f size, std::string path)
{
	this->position = position;
	this->size = size;
	if (!texture.loadFromFile(path))
	{
		std::cout << "GUIImage failed to load texture";
		window->close();
		exit(EXIT_FAILURE);
	}
	sprite.setTexture(texture);
	keepAspectRatio = false;
	hitbox = new Hitbox(sf::Vector2f(0.f, 0.f), sf::Vector2f(1.f, 1.f));
	hitbox->AddShape(new HitboxRect(position, size));
	origin = sf::Vector2f(.5f, .5f);
}
void GUIImage::Render()
{
	hitbox->shapes[0]->currentPos = position;
	sf::Vector2u texSize = texture.getSize();
	sf::Vector2f cPos(position.x * width, position.y * height);
	sf::Vector2f cSize(size.x * width, size.y * height);
	float widthMult = ((float)texSize.x) / (cSize.x * 2.f);
	float heightMult = ((float)texSize.y) / (cSize.y * 2.f);
	if (keepAspectRatio)
	{
		float widthMult = ((float)texSize.x) / (cSize.x * 2.f);
		float heightMult = ((float)texSize.y) / (cSize.y * 2.f);
		float scale;
		if (widthMult > heightMult)
		{
			scale = 1.f / widthMult;
		}
		else
		{
			scale = 1.f / heightMult;
		}
		sprite.setScale(scale, scale);
	}
	else
	{
		sprite.setScale(1.f / widthMult, 1.f / heightMult);
	}
	sprite.setPosition(cPos);
	sf::FloatRect bounds = sprite.getLocalBounds();
	sf::Vector2f topleft(bounds.left, bounds.top);
	sf::Vector2f origin(bounds.width * this->origin.x, bounds.height * this->origin.y);
	sprite.setOrigin(topleft + origin);
	sprite.setPosition(cPos - cSize + 2.f * sf::Vector2f(this->origin.x * cSize.x, this->origin.y * cSize.y));
	sf::FloatRect finalBounds = sprite.getGlobalBounds();
	sf::Vector2f s = sf::Vector2f(bounds.width * sprite.getScale().x, bounds.height * sprite.getScale().y);
	hitbox->shapes[0]->currentSize = sf::Vector2f(bounds.width * sprite.getScale().x / 2.f / width, bounds.height * sprite.getScale().y / 2.f / height);
	sf::Vector2f mid(finalBounds.left + s.x / 2.f, finalBounds.top + s.y / 2.f);
	hitbox->shapes[0]->currentPos = sf::Vector2f(mid.x / width, mid.y / height);
	window->draw(sprite);
}

void GUIImage::RenderToTexture(sf::RenderTexture* texture)
{
	hitbox->shapes[0]->currentPos = position;
	sf::Vector2u texSize = this->texture.getSize();
	sf::Vector2f cPos(position.x * width, position.y * height);
	sf::Vector2f cSize(size.x * width, size.y * height);
	float widthMult = ((float)texSize.x) / (cSize.x * 2.f);
	float heightMult = ((float)texSize.y) / (cSize.y * 2.f);
	if (keepAspectRatio)
	{
		float widthMult = ((float)texSize.x) / (cSize.x * 2.f);
		float heightMult = ((float)texSize.y) / (cSize.y * 2.f);
		float scale;
		if (widthMult > heightMult)
		{
			scale = 1.f / widthMult;
		}
		else
		{
			scale = 1.f / heightMult;
		}
		sprite.setScale(scale, scale);
	}
	else
	{
		sprite.setScale(1.f / widthMult, 1.f / heightMult);
	}
	sprite.setPosition(cPos);
	sf::FloatRect bounds = sprite.getLocalBounds();
	sf::Vector2f topleft(bounds.left, bounds.top);
	sf::Vector2f origin(bounds.width * this->origin.x, bounds.height * this->origin.y);
	sprite.setOrigin(topleft + origin);
	sprite.setPosition(cPos - cSize + 2.f * sf::Vector2f(this->origin.x * cSize.x, this->origin.y * cSize.y));
	sf::FloatRect finalBounds = sprite.getGlobalBounds();
	sf::Vector2f s = sf::Vector2f(bounds.width * sprite.getScale().x, bounds.height * sprite.getScale().y);
	hitbox->shapes[0]->currentSize = sf::Vector2f(bounds.width * sprite.getScale().x / 2.f / width, bounds.height * sprite.getScale().y / 2.f / height);
	sf::Vector2f mid(finalBounds.left + s.x / 2.f, finalBounds.top + s.y / 2.f);
	hitbox->shapes[0]->currentPos = sf::Vector2f(mid.x / width, mid.y / height);
	texture->draw(sprite);
}

GUIImage::~GUIImage()
{
}