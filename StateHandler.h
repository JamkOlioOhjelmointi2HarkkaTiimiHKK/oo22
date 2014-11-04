/*
* 15.10.2014 Tein tilakoneen ja annoin enumille mahdolliset tilat
* Tuomas Kyttä
*
*
*
* 
*/
#pragma once
#include <fstream>
#include <SFML/Graphics.hpp>
#include "Controls.h"
#include "Content.h"
#include "globals.h"
#include "Button.h"
#include "player.h"
#include "Play.h"
using namespace sf;

class StateHandler
{
private:
	enum gameState {uninitialized, menu, options, play, exit};

	struct optionValues{
		bool isVsync;
		int fpsLimit;
		ContextSettings settings;
		bool isFullScreen;
	};
	optionValues optionsStruct;
	RenderWindow window;
	Clock clock, secondClock;
	Time elapsedTime;
	Text title;
	float titleAnimation;

	Button playButton, optionsButton, exitButton, backButton;
	Button applyButton, vsyncButton, fpsLimitButton, antiAliasingButton, fullScreenButton;

	bool showDebug, secondPassed;
	int fps;
	float dt;

	void loopGame();

	void runMenu();
	void updateMenu();
	void drawMenu(RenderWindow &window);
	void initializeMenu();

	void runOptions();
	void updateOptions();
	void drawOptions(RenderWindow &window);
	void applyOptionSettings();
	void initializeOptions();
	void changeVsync();
	void changeFPSLimit();
	void changeAA();
	void changeFullScreen();

	void handleControls(RenderWindow &window);
	void handleTime();

	gameState state;
	
public:

	StateHandler();
	~StateHandler();

	void startGame();
	bool exitGame();
	void setState(gameState);
};

