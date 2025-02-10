#include "ConveyorType.hpp"

//abstract class for structures that behave like a conveyor.

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
//this was going to be for upgraded conveyors that could move items faster, however i decided not to implement this as
//throughput was not an issue during testing.
void ConveyorType::SetUpgradeLevel(int level)
{
	upgradeLevel = level;
	if (upgradeLevel == 0)
	{
		speed = 3.f;
	}
	else if (upgradeLevel == 1)
	{
		speed = 6.f;
	}
}

void ConveyorType::Progress(float dt)
{}
void ConveyorType::TryAdd()
{}
void ConveyorType::KeepDistance()
{}