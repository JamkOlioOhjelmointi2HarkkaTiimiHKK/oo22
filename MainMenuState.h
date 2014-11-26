#pragma once
#include <SFML\Graphics.hpp>
#include "StateHandler.h"

class MainMenuState{
private:
	Clock clock, secondClock;
	Time elapsedTime;
	Text title;
	std::vector<Button*> buttons;
	bool showDebug, secondPassed, menuModeIsActive, startPlayState, showOptions;
	int fps;
	float dt;
	float titleAnimation;
public:
	MainMenuState();
	~MainMenuState();

	bool runMainMenuState();
	void initializeMainMenuState();
	void updateMainMenuState();
	void drawMainMenuState();
	void updateOptionsMenuState();
	void drawOptionsMenuState();
	void handleControls();
	void handleTime();
};