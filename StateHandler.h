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
public:

	StateHandler();

	void gameStart();
	bool gameExit();
	void gameLoop();
	void showMenu();
	void showPlay();

	gameState state;

	~StateHandler();
};

