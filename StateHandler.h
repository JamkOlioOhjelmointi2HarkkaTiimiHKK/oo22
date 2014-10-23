/*
* 15.10.2014 Tein tilakoneen ja annoin enumille mahdolliset tilat
*
*
*
*
* Tuomas Kytt�
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
	enum gameState {uninitialized, menu, edit, exit}; // vaihtoehtoinen tapa teh�, tehd��n state pointteri ja muutetaan sen sis�lt��
	//EditorState *editState; jos haluat teh� fiinej� tiloja
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

