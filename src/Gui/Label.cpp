#include "Gui/Label.hpp"
#include "Main.hpp"
#include "utils.hpp"
Label::Label(std::string text, sf::FloatRect bounds, sf::Color col)
{
	this->text = text;
	this->bounds = bounds;
	this->col = col;
	label = sf::Text();
	label.setFont(*defaultFont);
	label.setString(text);
	label.setFillColor(col);
	origin = sf::Vector2f(0.5f, 0.5f);
}
Label::Label(std::string text, sf::Vector2f pos, sf::Vector2f size, sf::Color col)
{
	this->text = text;
	this->bounds = sf::FloatRect(pos.x - size.x / 2.f, pos.y - size.y / 2.f, size.x, size.y);
	this->col = col;
	label.setFont(*defaultFont);
	label.setString(text);
	label.setFillColor(col);
	origin = sf::Vector2f(0.5f, 0.5f);
}
void Label::SetText(std::string text)
{
	label.setString(text);
}
void Label::SetCol(sf::Color col)
{
	label.setFillColor(col);
}
void Label::Render()
{
	if (label.getString() == "")
	{
		return;
	}
	sf::Vector2f padding(0.02f * width, 0.02f * height);

	GetMaxFontSize(&label, sf::Vector2f(bounds.width * width - padding.x, bounds.height * height - padding.y));
	sf::FloatRect tBounds = label.getLocalBounds();
	label.setOrigin((int)((tBounds.left + tBounds.width) * origin.x), (int)((tBounds.top + tBounds.height) * origin.y));
	label.setPosition((int)((bounds.left + bounds.width * origin.x) * width), (int)((bounds.top + bounds.height * origin.y) * height));
	window->draw(label);
}
Label::~Label()
{}

void Label::setOrigin(sf::Vector2f origin)
{
	this->origin = origin;
}