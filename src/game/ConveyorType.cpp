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