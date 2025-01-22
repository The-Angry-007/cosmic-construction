#include "ConveyorType.hpp"

ConveyorType::ConveyorType()
{}
ConveyorType::~ConveyorType()
{}
bool ConveyorType::TryAddItem(int index, int direction, float progress)
{
	return false;
}
bool ConveyorType::CanAddItem(int direction, float progress)
{
	return false;
}
float ConveyorType::Distance(int direction)
{
	return 0.f;
}

bool ConveyorType::AcceptsItems(int direction)
{
	return false;
}