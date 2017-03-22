#pragma once
#include <SFML\Graphics.hpp>
#include "StateHandler.h"

class OptionsState{
private:
	bool showDebug, secondPassed;
public:
	OptionsState();
	~OptionsState();

	void runOptionsState();
	void updateOptionsState();
	void drawOptionsState();
};