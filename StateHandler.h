/*
* 15.10.2014 Tein tilakoneen ja annoin enumille mahdolliset tilat
*
*
*
*
* Tuomas Kyttä
*/
#pragma once
#include "main.h"
#include "Controls.h"
#include "Content.h"

//class EditorState;
//class MainMenu;

class StateHandler
{
private:
	enum gameState {uninitialized, menu, edit, exit}; // vaihtoehtoinen tapa tehä, tehdään state pointteri ja muutetaan sen sisältöä
	//EditorState *editState; jos haluat tehä fiinejä tiloja
	//MainMenu *mainMenu;

public:

	StateHandler();

	void editStart();
	bool editExit();
	void editLoop();
	void showMenu();

	gameState state;

	~StateHandler();
};

