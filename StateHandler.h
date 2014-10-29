/*
* 15.10.2014 Tein tilakoneen ja annoin enumille mahdolliset tilat
* Tuomas Kytt�
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
using namespace sf;
class StateHandler
{
private:
	enum gameState {uninitialized, menu, play, exit};
	RenderWindow window;
	Clock clock;
	Time elapsedTime;
	bool showDebug;
	int fps;
	float dt;
public:

	StateHandler();

	void gameStart();
	bool gameExit();
	void gameLoop();
	void runMenu();
	void runPlay();

	void handleControls();
	void handleTime();

	gameState state;

	~StateHandler();
};

