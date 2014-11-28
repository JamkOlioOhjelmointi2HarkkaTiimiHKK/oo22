#include "StateHandler.h"

StateHandler::StateHandler()
{
	state = uninitialized;

	editState = new EditorState();
}

void StateHandler::startGame()
{
	if (state != uninitialized)
		return;
	state = menu;

	while (!exitGame())
	{			
		loopGame();
	}
	window.close();
}

bool StateHandler::exitGame()
{
	if (state == exit)
		return true;
	else
		return false;
}

void StateHandler::loopGame()
{	
	Event currentEvent;
	if (window.pollEvent(currentEvent))
	{
		if (currentEvent.type == Event::Closed)
			state = exit;
	}

	Controls::get()->update(window);
	switch (state)
	{
		case menu:
		{
			
			MainMenuState menuMode;
			menuMode.runMainMenuState();
			MainMenuState::gameState result = menuMode.state;

			merge = new Merge();

			switch (result)
			{
			case MainMenuState::play:
				state = play;
				break;
			case MainMenuState::edit:
				state = edit;
				break;
			case MainMenuState::mergeState:
				state = mergeState;
				break;
			case MainMenuState::exit:
				state = exit;
				break;
			}
			break;
		}

		case play:
		{
			PlayState playMode;
			if (playMode.runPlayState())
				state = menu;
			else
				state = exit;
			break;
		}
		case edit:
		{
			editState->loop();
				if (Controls::get()->kIsPressed(sf::Keyboard().Escape))
				{
					state = menu;
				}
				break;
		}
		case mergeState:
			
			merge->loop(dt);
			handleTime();
			if (Controls::get()->kIsPressed(sf::Keyboard().Escape))
			{
				state = menu;
			}
			break;
	}
	
}

void StateHandler::handleTime(){

	dt = clock.restart().asSeconds();

	if (elapsedTime.asMilliseconds() >= 1000){
		secondClock.restart();
		secondPassed = true;
		fps = 0;
	}
	else{
		fps++;
		secondPassed = false;
	}
}

StateHandler::~StateHandler()
{
	delete merge;
	delete editState;
}