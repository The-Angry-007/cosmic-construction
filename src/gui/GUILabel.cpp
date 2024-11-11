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
	sf::Vector2f cPos(position.x * width, position.y * height);
	sf::Vector2f cSize(size.x * width, size.y * height);
	//find maximum character scale that fits in bounds
	text.setScale(sf::Vector2f(1.f, 1.f));
	text.setCharacterSize(64);
	sf::FloatRect bounds = text.getLocalBounds();
	float widthMult = bounds.width / cSize.x;
	float heightMult = bounds.height / cSize.y;
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
	sf::Vector2f topleft(newBounds.left, newBounds.top);
	sf::Vector2f origin(newBounds.width * this->origin.x, newBounds.height * this->origin.y);
	text.setOrigin(topleft + origin);
	text.setPosition(cPos - cSize + 2.f * sf::Vector2f(this->origin.x * cSize.x, this->origin.y * cSize.y));

	window->draw(text);
}