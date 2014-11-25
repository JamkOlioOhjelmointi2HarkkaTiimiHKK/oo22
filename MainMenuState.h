#pragma once
#include <SFML\Graphics.hpp>
#include "StateHandler.h"

class MainMenuState{
private:
	std::vector<Button*> buttons;
	bool showDebug, secondPassed;

public:
	MainMenuState();
	~MainMenuState();

	void runMainMenuState();
	void updateMainMenuState();
	void drawMainMenuState();
};