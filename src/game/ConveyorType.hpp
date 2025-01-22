#pragma once
#include "Structure.hpp"
class ConveyorType : public Structure
{
public:
	float gap;
	ConveyorType();
	~ConveyorType();
	virtual bool TryAddItem(int index, int direction, float progress);
	virtual float Distance(int direction);
	virtual bool CanAddItem(int direction, float progress);
};