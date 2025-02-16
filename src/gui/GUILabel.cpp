#include "GUILabel.hpp"
#include "Main.hpp"
#include "utils.hpp"
GUILabel::GUILabel(sf::Vector2f position, sf::Vector2f size, std::string text)
{
	//attempt to load default font
	// if (!font.loadFromFile("resources/fonts/default font.ttf"))
	// {
	// 	std::cout << "gui label failed to load default font" << std::endl;
	// 	//this ends the program immediately
	// 	window->close();
	// 	exit(EXIT_FAILURE);
	// }
	this->position = position;
	this->size = size;
	this->value = text;
	color = sf::Color::White;
	this->text.setFillColor(color);
	this->text.setString(this->value);
	this->text.setFont(guihandler.guifont);
	origin = sf::Vector2f(0.5f, 0.5f);
	altCharSize = false;
	hitbox = nullptr;
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
	text.setCharacterSize(128);
	if (true)
	{
		int numLines = 1;
		for (int i = 0; i < value.size(); i++)
		{
			if (value[i] == '\n')
			{
				numLines++;
			}
		}
		text.setCharacterSize(ceil(((floor(cSize.y / numLines) + 1)) * 3.f));
	}
	text.setScale(sf::Vector2f(1.f, 1.f));

	sf::FloatRect bounds = text.getLocalBounds();

	float widthMult = ((float)bounds.width) / (cSize.x * 2.f);
	float heightMult = ((float)bounds.height) / (cSize.y * 2.f);
	float scale;
	if (widthMult > heightMult)
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
	text.setPosition((sf::Vector2f)(sf::Vector2i)text.getPosition());

	window->draw(text);
}

void GUILabel::RenderToTexture(sf::RenderTexture* texture)
{
	text.setString(this->value);
	sf::Vector2f cPos((float)position.x * width, (float)position.y * height);
	sf::Vector2f cSize((float)size.x * width, (float)size.y * height);
	//find maximum character scale that fits in bounds
	text.setOrigin(0.f, 0.f);
	text.setScale(sf::Vector2f(1.f, 1.f));
	text.setCharacterSize(128);
	if (false)
	{
		text.setCharacterSize(ceil(((floor(cSize.y) + 1)) * 3.f));
	}

	sf::FloatRect bounds = text.getLocalBounds();

	float widthMult = ((float)bounds.width) / (cSize.x * 2.f);
	float heightMult = ((float)bounds.height) / (cSize.y * 2.f);
	float scale;
	if (widthMult > heightMult)
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
	text.setPosition((sf::Vector2f)(sf::Vector2i)text.getPosition());

	texture->draw(text);
}

void GUILabel::DoWrapping(int charsPerLine)
{
	if (value == "")
	{
		return;
	}
	std::string newVal = "";
	std::vector<std::string> lines = Split(value, '\n');
	for (int i = 0; i < lines.size(); i++)
	{
		int length = lines[i].size();
		if (length <= charsPerLine)
		{
			continue;
		}
		else
		{
			int wordCount = 0;
			int charCount = 0;

			std::vector<std::string> words = Split(lines[i], ' ');
			while (charCount <= charsPerLine)
			{
				charCount += words[wordCount].size() + 1;
				wordCount++;
			}
			std::string nextLine = "";
			for (int i = wordCount; i < words.size(); i++)
			{
				nextLine += words[i];
				if (i != words.size() - 1)
				{
					nextLine += " ";
				}
			}
			lines.insert(lines.begin() + i + 1, nextLine);
			std::string currLine = "";
			for (int i = 0; i < wordCount; i++)
			{
				currLine += words[i];
				if (i != wordCount - 1)
				{
					currLine += " ";
				}
			}
			lines[i] = currLine;
		}
	}
	for (int i = 0; i < lines.size(); i++)
	{
		newVal += lines[i];
		if (i != lines.size() - 1)
		{
			newVal += '\n';
		}
	}
	value = newVal;
}

GUILabel::~GUILabel()
{
}