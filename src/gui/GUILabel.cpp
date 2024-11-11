#include "GUILabel.hpp"
#include "Main.hpp"
GUILabel::GUILabel(sf::Vector2f position, sf::Vector2f size, std::string text)
{
	//attempt to load default font
	if (!font.loadFromFile("resources/fonts/default font.ttf"))
	{
		std::cout << "gui label failed to load default font" << std::endl;
		//this ends the program immediately
		window->close();
		exit(EXIT_FAILURE);
	}
	this->position = position;
	this->size = size;
	this->value = text;
	color = sf::Color::White;
	this->text.setFillColor(color);
	this->text.setString(this->value);
	this->text.setFont(font);
	origin = sf::Vector2f(0.5f, 0.5f);
}
void GUILabel::SetColor(sf::Color color)
{
	text.setFillColor(color);
	this->color = color;
}

void GUILabel::Render()
{
	text.setString(this->value);
	sf::Vector2f cPos((float)position.x * width, (float)position.y * height);
	sf::Vector2f cSize((float)size.x * width, (float)size.y * height);
	//find maximum character scale that fits in bounds
	text.setOrigin(0.f, 0.f);
	text.setScale(sf::Vector2f(1.f, 1.f));
	text.setCharacterSize(128);
	sf::FloatRect bounds = text.getLocalBounds();
	std::cout << bounds.left << " " << bounds.top << " " << bounds.width << " " << bounds.height << std::endl;

	float widthMult = ((float)bounds.width) / cSize.x;
	float heightMult = ((float)bounds.height) / cSize.y;
	float scale;
	if (widthMult < heightMult)
	{
		scale = 1.f / widthMult;
	}
	else
	{
		scale = 1.f / heightMult;
	}
	text.setScale(sf::Vector2f(scale, scale));
	sf::FloatRect newBounds = text.getLocalBounds();
	//std::cout << newBounds.left << " " << newBounds.top << " " << newBounds.width << " " << newBounds.height << std::endl;
	sf::Vector2f topleft(newBounds.left, newBounds.top);
	sf::Vector2f origin(newBounds.width * this->origin.x, newBounds.height * this->origin.y);
	text.setOrigin(topleft + origin);
	text.setPosition(cPos - cSize + 2.f * sf::Vector2f(this->origin.x * cSize.x, this->origin.y * cSize.y));
	text.setPosition((sf::Vector2f)(sf::Vector2i)text.getPosition());

	window->draw(text);
}