#pragma once
#include <fstream>
#include <SFML/Graphics.hpp>
#include "Controls.h"
#include "Content.h"
#include "globals.h"
#include "Button.h"
using namespace sf;

class MainMenuState{
private:
	Clock clock, secondClock;
	Time elapsedTime;
	Text title;
	std::vector<Button*> menuButtons, optionButtons;
	bool showDebug, secondPassed, showOptions, menuModeIsActive;
	int fps;
	float dt;
	float titleAnimation;

	struct OptionValues {
		bool isVsync;
		int fpsLimit;
		ContextSettings settings;
		bool isFullScreen;
	};
	

public:

	OptionValues optionsStruct;

	enum gameState { uninitialized, menu, play, edit, mergeState, exit };
	gameState state;

	MainMenuState();
	~MainMenuState();

	void runMainMenuState();
	void updateMainMenuState();
	void drawMainMenuState();

	void updateOptionsMenuState();
	void drawOptionsMenuState();
	void changeVsync();
	void changeFPSLimit();
	void changeAA();
	void changeFullScreen();
	void applyOptionSettings();

	void handleControls();
	void handleTime();
};