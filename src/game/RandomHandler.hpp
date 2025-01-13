#pragma once
#include "PerlinNoise.hpp"
namespace RandomHandler
{
extern uint64_t seed;
extern uint64_t currentNum;
extern siv::PerlinNoise sivnoise;
uint64_t GetNextNumber();
void SetNum(sf::Vector2i chunkPos);
void SetSeed(uint64_t seed);
float getNoise(int x, int y);
};