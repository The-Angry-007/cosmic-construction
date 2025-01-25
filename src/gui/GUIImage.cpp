#include "GUIImage.hpp"
#include "Main.hpp"
//constructor - takes position, size and path to the image file to be used
GUIImage::GUIImage(sf::Vector2f position, sf::Vector2f size, std::string path)
{
	this->position = position;
	this->size = size;
	if (path != "")
	{
		if (!texture.loadFromFile(path))
		{
			std::cout << "GUIImage failed to load texture";
			window->close();
			exit(EXIT_FAILURE);
		}
		sprite.setTexture(texture);
	}
	//do not keep the aspect ratio by default
	keepAspectRatio = false;
	hitbox = new Hitbox(sf::Vector2f(0.f, 0.f), sf::Vector2f(1.f, 1.f));
	//the hitbox is a rectangle the size of  the image
	hitbox->AddShape(new HitboxRect(position, size));
	//image's origin is its centre
	origin = sf::Vector2f(.5f, .5f);
}

//render
void GUIImage::Render()
{
	//update position of hitbox
	hitbox->shapes[0]->currentPos = position;
	//get size of texture
	// sf::Vector2u texSize = texture.getSize();
	sf::Vector2u texSize(sprite.getTextureRect().width, sprite.getTextureRect().height);
	//scale position and size to be in terms of pixels
	sf::Vector2f cPos(position.x * width, position.y * height);
	sf::Vector2f cSize(size.x * width, size.y * height);
	//what the x scale should be to fit the desired size
	float widthMult = ((float)texSize.x) / (cSize.x * 2.f);
	//what the y scale should be
	float heightMult = ((float)texSize.y) / (cSize.y * 2.f);
	//if trying to keep the aspect ratio:
	if (keepAspectRatio)
	{
		float scale;
		//width is the limiting factor so use that for the scale
		if (widthMult > heightMult)
		{
			scale = 1.f / widthMult;
		}
		//otherwise use the height
		else
		{
			scale = 1.f / heightMult;
		}
		//set the scale of the sprite
		sprite.setScale(scale, scale);
	}
	//otherwise just use the scales calculated
	else
	{
		sprite.setScale(1.f / widthMult, 1.f / heightMult);
	}
	sprite.setPosition(cPos);
	sf::FloatRect bounds = sprite.getLocalBounds();
	sf::Vector2f origin(bounds.width * this->origin.x, bounds.height * this->origin.y);
	//set the origin of the sprite
	sprite.setOrigin(origin);
	//some complicated maths to adjust the position: position - current size + 2 * (origin scaled by size)
	//this is essentially the topleft corner + the position of the origin
	sprite.setPosition(cPos - cSize + 2.f * sf::Vector2f(this->origin.x * cSize.x, this->origin.y * cSize.y));
	//get the new bounds after shifting
	sf::FloatRect finalBounds = sprite.getGlobalBounds();
	//get the size of the sprite
	sf::Vector2f s = sf::Vector2f(bounds.width * sprite.getScale().x, bounds.height * sprite.getScale().y);
	//use this to update the hitbox
	hitbox->shapes[0]->currentSize = sf::Vector2f(bounds.width * sprite.getScale().x / 2.f / width, bounds.height * sprite.getScale().y / 2.f / height);
	sf::Vector2f mid(finalBounds.left + s.x / 2.f, finalBounds.top + s.y / 2.f);
	hitbox->shapes[0]->currentPos = sf::Vector2f(mid.x / width, mid.y / height);
	//draw the sprite
	window->draw(sprite);
}
//this is the exact same as the render function, but at the end it is drawn to a render texture instead of the window.
void GUIImage::RenderToTexture(sf::RenderTexture* texture)
{
	hitbox->shapes[0]->currentPos = position;
	sf::Vector2u texSize(sprite.getTextureRect().width, sprite.getTextureRect().height);
	// sf::Vector2u texSize = this->texture.getSize();
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

//nothing to destruct
GUIImage::~GUIImage()
{
}