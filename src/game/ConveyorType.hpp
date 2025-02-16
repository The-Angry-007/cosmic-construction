#pragma once
#include "Structure.hpp"
class ConveyorType : public Structure
{
public:
	float gap;
	float speed;
	int upgradeLevel = 0;
	ConveyorType();
	~ConveyorType();
	virtual void Progress(float dt);
	virtual void TryAdd();
	virtual void KeepDistance();
	virtual bool TryAddItem(int index, int direction, float progress);
	virtual float Distance(int direction);
	virtual bool CanAddItem(int direction, float progress);
	virtual bool AcceptsItems(int direction);
	virtual void SetUpgradeLevel(int level);
};