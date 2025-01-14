#include "SaplingPlanter.hpp"
#include "Main.hpp"
#include "ResourceHandler.hpp"
SaplingPlanter::SaplingPlanter(int id, int planetID, int direction)
{
	SetID(id);
	this->planetID = planetID;
	topSprite = sf::Sprite();
	typeID = 4;
	ResourceHandler::structureAtlas->SetSprite(topSprite, 4, 1);
	sprite = sf::Sprite();
	ResourceHandler::structureAtlas->SetSprite(sprite, 4, 0);
	timeSinceTree = 0.f;
	placedByPlayer = true;
	tileSize = ResourceHandler::structureSizes[typeID];
	tree = -1;
}

void SaplingPlanter::SetPosition(sf::Vector2i pos)
{
	Structure::SetPosition(pos);
	topSprite.setPosition(sprite.getPosition());
	std::cout << sprite.getPosition().x << " " << sprite.getPosition().y << std::endl;
}

void SaplingPlanter::Update(float dt)
{
	Planet& p = game->planets[planetID];
	if (tree == -1)
	{
		timeSinceTree += dt;
		if (timeSinceTree > 10.f)
		{
			Tree* tree = new Tree(-1, planetID);
			tree->parent = id;
			p.AddStructure(tree);
			sf::Vector2i pos = position;
			pos += p.GetChunk(chunkID)->position * CHUNK_SIZE;
			tree->SetPosition(pos);
			timeSinceTree = 0.f;
			this->tree = tree->id;
		}
	}
}
void SaplingPlanter::Render()
{
	Planet& p = game->planets[planetID];
	p.renderObjects.push_back(RenderObject {
		&sprite,
		0 });
	p.renderObjects.push_back(RenderObject {
		&topSprite,
		18 });
}

void SaplingPlanter::RenderPreview()
{
	int opacity = 100;
	sf::Color col = sf::Color::Green;

	if (!CanBePlaced())
	{
		col = sf::Color(255, 100, 100);
	}
	col.a = opacity;
	sprite.setColor(col);
	Planet& p = game->planets[planetID];
	p.renderObjects.push_back(RenderObject {
		&sprite,
		2000 });
}

JSON SaplingPlanter::ToJSON()
{
	JSON j = JSON();
	j.AddAttribute("Position", position);
	j.AddAttribute("ChunkID", chunkID);
	j.AddAttribute("TypeID", typeID);
	j.AddAttribute("ID", id);
	j.AddAttribute("TimeSinceTree", timeSinceTree);
	j.AddAttribute("Tree", tree);
	return j;
}

void SaplingPlanter::FromJSON(JSON j)
{
	sf::Vector2i pos = j.GetV2i("Position");
	chunkID = j.GetInt("ChunkID");
	id = j.GetInt("ID");
	timeSinceTree = j.GetFloat("TimeSinceTree");
	tree = j.GetInt("Tree");
	pos += game->planets[planetID].GetChunk(chunkID)->position * CHUNK_SIZE;
	SetPosition(pos);
}