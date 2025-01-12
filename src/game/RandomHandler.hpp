#pragma once
namespace RandomHandler
{
extern uint64_t seed;
extern uint64_t currentNum;
uint64_t GetNextNumber();
void SetNum(sf::Vector2i chunkPos);
void SetSeed(uint64_t seed);
};