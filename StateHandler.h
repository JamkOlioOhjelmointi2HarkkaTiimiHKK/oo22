#pragma once
#include <fstream>
#include <SFML/Graphics.hpp>
#include "Controls.h"
#include "Content.h"
#include "globals.h"
#include "Button.h"
#include "player.h"
#include "MainMenuState.h"
#include "PlayState.h"
#include "EditorState.h"
#include "Merge.h"
using namespace sf;

class EditorState;
class Merge;

class StateHandler
{
private:
	enum gameState { uninitialized, menu, options, play, edit, mergeState, exit };

	std::vector<Button*> buttons;

	EditorState *editState;
	Merge *merge;

	struct optionValues{
		bool isVsync;
		int fpsLimit;
		ContextSettings settings;
		bool isFullScreen;
	};
	optionValues optionsStruct;
	Clock clock, secondClock;
	Time elapsedTime;
	Text title;
	float titleAnimation;

	Button applyButton, backButton, vsyncButton, fpsLimitButton, antiAliasingButton, fullScreenButton;

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

	void editStart();
	void editLoop();

	void startGame();
	bool exitGame();
	void setState(gameState);
};

