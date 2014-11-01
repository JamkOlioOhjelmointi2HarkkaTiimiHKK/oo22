/*
* 15.10.2014 Tein tilakoneen ja annoin enumille mahdolliset tilat
* Tuomas Kyttä
*
*
*
* 
*/
#pragma once
#include <SFML/Graphics.hpp>
#include "Controls.h"
#include "Content.h"
#include "globals.h"
#include "Button.h"
#include "player.h"
using namespace sf;
class StateHandler
{
private:
	enum gameState {uninitialized, menu, options, play, exit};
	ContextSettings settings;
	RenderWindow window;
	Clock clock, secondClock;
	Time elapsedTime;
	bool showDebug, secondPassed;
	int fps;
	float dt;
public:

	StateHandler();

	void startGame();
	bool exitGame();
	void loopGame();
	void runMenu();
	void updateMenu(Button, Button, Button);
	void drawMenu(RenderWindow &window);

	void runOptions();

	void runPlay();
	
	void handleControls(RenderWindow &window);
	void handleTime();

	void setState(gameState);

	gameState state;

	~StateHandler();
};

