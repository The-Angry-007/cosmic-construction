#pragma once
#include "../PCH.hpp"
#include "../gui.hpp"
class Tutorial
{
public:
	int currentPhase;
	std::vector<std::vector<int>> validCodes;
	std::vector<std::string> script;
	std::vector<bool> skippables;
	GUI* gui;
	~Tutorial();
	Tutorial();
	void Update(float dt);
	void Render();
	void SwitchPhase(int phase);
	void LimitInputs();
	void EndTutorial();
};