#pragma once
#include <SFML\Graphics.hpp>
#include "Controls.h"
#include "Content.h"
#include "globals.h"
#include "Button.h"
using namespace sf;

class MainMenuState{
private:
	enum gameState { uninitialized, menu, options, play, edit, mergeState, exit };
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
	void updateMainMenuState();
	void drawMainMenuState();
	void updateOptionsMenuState();
	void drawOptionsMenuState();
	void handleControls();
	void handleTime();
};