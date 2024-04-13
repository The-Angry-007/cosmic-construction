#pragma once
#include "box2d/box2d.h"
#include "parts/Part.hpp"
class Structure
{
public:
	std::vector<Part*> parts;
	std::vector<std::vector<int>> connections;
	std::vector<b2WeldJoint> joints;
	//centre of mass
	b2Vec2 com;
	bool focused = false;
	Structure();
	void AddPart(Part* part);
	void AddConnection(int part1, int part2);
	void AddConnection(Part* part1, Part* part2);
	void Update(double dt);
	void CentreCamera();
	void Render();
	void ResetCOM();
	void GetRotation();
	float rotation;
	std::string toString();
	Structure(std::vector<std::string> saveStrings);
};