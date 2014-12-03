#pragma once
#include <SFML/Graphics.hpp>
#include "Content.h"
#include "globals.h"
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
	gameState state;

	EditorState *editState;
	Merge *merge;

	Clock clock, secondClock;
	Time elapsedTime;


	bool secondPassed;
	int fps;
	float dt;

	void loopGame();

	void handleTime();
	
public:

	StateHandler();
	~StateHandler();

	void editStart();
	void editLoop();

	void startGame();
	bool exitGame();
	void setState(gameState);

	void drawLoadingScreen();
};

