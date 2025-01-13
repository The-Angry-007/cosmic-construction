#include "RandomHandler.hpp"
#include "PerlinNoise.hpp"
namespace RandomHandler
{
uint64_t seed;
uint64_t currentNum;
siv::PerlinNoise sivnoise;
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
	sivnoise.reseed(seed);
}

float RandomHandler::getNoise(int x, int y)
{
	return sivnoise.noise2D_01(x * 0.1f, y * 0.1f);
}