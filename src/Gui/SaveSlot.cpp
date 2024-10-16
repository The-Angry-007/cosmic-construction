#include "Include.hpp"
SaveSlot::SaveSlot(std::string path, sf::Vector2f pos, sf::Vector2f size)
{
	this->path = path;
	std::string dir = SaveHandler::workingDir + "\\" + path + "\\metadata.txt";
	this->pos = pos;
	this->size = size;
	button = new Button(pos, size, sf::Color(50, 50, 50), "");
	std::vector<std::string> data = SaveHandler::getLines(dir);
	labels.push_back(new Label("made on " + data[0], sf::FloatRect(pos.x - size.x * 0.45f, pos.y - size.y * 0.1f, size.x / 2.f, size.y * 0.5f), sf::Color::White));
	labels[0]->setOrigin(sf::Vector2f(0.f, 1.f));
	labels.push_back(new Label(path, sf::FloatRect(pos.x - size.x * 0.45f, pos.y - size.y * 0.5f, size.x / 2.f, size.y / 2.f), sf::Color::White));
	labels[1]->setOrigin(sf::Vector2f(0.f, 0.f));
	int seconds = std::stoi(data[2]);

	float toDisplay = seconds;
	std::string units = "s";
	if (seconds > 60)
	{
		float mins = seconds / 60.f;
		toDisplay = mins;
		units = "m";
		if (mins > 60)
		{
			float hours = mins / 60.f;
			toDisplay = hours;
			units = "h";
		}
	}
	std::stringstream ss;
	ss << std::fixed << std::setprecision(1) << toDisplay;
	std::string s = "time played: " + ss.str() + units;
	labels.push_back(new Label(s, sf::FloatRect(pos.x - size.x * 0.05f, pos.y - size.y * 0.1f, size.x / 2.f, size.y / 2.f), sf::Color::White));
	labels[2]->setOrigin(sf::Vector2f(1.f, 1.f));
	//check whether valid version
	int version = -1;
	if (data.size() >= 4)
	{
		version = std::stoi(data[3]);
	}
	if (version == SaveHandler::saveVersion)
	{
		validVersion = true;
	}
	else
	{
		validVersion = false;
		labels = {};
		labels.push_back(new Label("Save made in outdated version", sf::FloatRect(pos.x - size.x * 0.5f, pos.y - size.y * 0.5f, size.x, size.y), sf::Color::Red));
	}
	speed = 5.f;
	targetPos = this->pos;
	for (uint i = 0; i < labels.size(); i++)
	{
		labels[i]->padding = sf::Vector2f(0.02f, 0.02f);
	}
}

void SaveSlot::Render()
{
	button->Render();
	for (uint i = 0; i < labels.size(); i++)
	{
		labels[i]->Render();
	}
}
void SaveSlot::Update(float dt)
{
	if (button->clicked() && validVersion)
	{
		onClick();
	}
	Interpolate(dt);
}
void SaveSlot::onClick()
{
	SaveHandler::workingDir += "\\" + path;
	menu.OpenMenu(4);
	game = new Game();
	//this is in fact not a new game, this is just for testing purposes
	game->Init(false);
}
SaveSlot::~SaveSlot()
{
	// delete button;
	// for (uint i = 0; i < labels.size(); i++)
	// {
	// 	delete labels[i];
	// }
}
void SaveSlot::Move(sf::Vector2f amt)
{
	targetPos += amt;
}
void SaveSlot::Interpolate(float dt)
{
	sf::Vector2f adjustment = (targetPos - pos) * speed * dt;
	pos += adjustment;
	for (uint i = 0; i < labels.size(); i++)
	{
		labels[i]->bounds.top += adjustment.y;
	}
	button->pos.y += adjustment.y;
}