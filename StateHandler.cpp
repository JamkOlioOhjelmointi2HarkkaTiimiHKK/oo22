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
//Pelin pää looppi, koko peli pyörii tässä.
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

			if (result != MainMenuState::exit){
				drawLoadingScreen();
				merge = new Merge();
			}
				

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
//Piirtää latausruudun raskaan latausajan väliin
void StateHandler::drawLoadingScreen(){
	window.clear(Color::Black);
	sf::Texture loadTexture;
	sf::Sprite loadSprite;
	loadTexture.loadFromFile("res/loadingScreen.png");
	loadSprite.setTexture(loadTexture);
	loadSprite.setPosition(50, SCREEN_HEIGHT - loadSprite.getGlobalBounds().height- 50);
	window.draw(loadSprite);
	window.display();
}
//päivittää kellot
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
//Destruktori
StateHandler::~StateHandler()
{
	delete merge;
	delete editState;
}