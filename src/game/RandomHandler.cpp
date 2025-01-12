#include "RandomHandler.hpp"

namespace RandomHandler
{
uint64_t seed;
uint64_t currentNum;
}

uint64_t RandomHandler::GetNextNumber()
{
	uint64_t x = currentNum;
	x ^= x << 13;
	x ^= x >> 7;
	x ^= x << 17;
	return currentNum = x;
}

void RandomHandler::SetNum(sf::Vector2i chunkPos)
{
	//y is multiplied by 131072
	currentNum = seed + chunkPos.x + (chunkPos.y << 17);
}

void RandomHandler::SetSeed(uint64_t seed)
{
	RandomHandler::seed = seed;
	SetNum(sf::Vector2i(0, 0));
	std::cout << RandomHandler::seed << std::endl;
}