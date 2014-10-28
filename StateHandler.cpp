#include "StateHandler.h"


StateHandler::StateHandler()
{
	state = uninitialized;
	window.create(VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "OO22");
	window.setVerticalSyncEnabled(true);
	showDebug = true;
}



void StateHandler::gameStart()
{
	if (state != uninitialized)
		return;
	state = menu;

	while (!gameExit())
	{			
		gameLoop();
	}

	window.close();
}

bool StateHandler::gameExit()
{
	if (state == exit)
		return true;
	else
		return false;
}

void StateHandler::gameLoop()
{	
	Event currentEvent;
	if (window.pollEvent(currentEvent))
	{
		if (currentEvent.type == Event::Closed)
			state = exit;

	}

	Controls::get()->update();
	switch (state)
	{
		case menu:
		{
			showMenu();
			break;
		}

		case play:
		{

			showPlay();
			//playState->update();
			window.clear(Color::Black);
			//playState->draw();
			window.display();

			if (Controls::get()->kIsPressed(sf::Keyboard().Escape))
			{
				//mainMenu->unInitialize();
				state = menu;
			}

		}
	}
}

void StateHandler::showMenu()
{
	//Controls::get()->update();
	window.clear(Color::Black);
	if (showDebug){
		window.draw(Content::get()->debugText);
	}
	window.display();

	//dt = time1.restart().asSeconds();
	//fps.setString(std::to_string((int)(1 / dt)));

	//MainMenu::menuResult result = mainMenu->action;


}

void StateHandler::showPlay(){

}

StateHandler::~StateHandler()
{

}
