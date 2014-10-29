#include "StateHandler.h"


StateHandler::StateHandler()
{
	state = uninitialized;
	window.create(VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "OO22");
	window.setVerticalSyncEnabled(true);
	showDebug = true;
	fps = 0;
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
			runMenu();
			break;
		}

		case play:
		{
			runPlay();
			break;
		}
	}
}

void StateHandler::runMenu()
{
	//Controls::get()->update(); Jos lisään sisäisen whilen niin tämä pitää säilyttää
	handleControls();

	window.clear(Color::Black);
	if (showDebug){
		window.draw(Content::get()->debugText);
	}
	window.display();

	handleTime();
}

void StateHandler::runPlay(){
	
	handleControls();

	window.clear(Color::Black);
	if (showDebug){
		window.draw(Content::get()->debugText);
	}
	window.display();

	handleTime();
}

void StateHandler::handleControls(){

	if (Controls::get()->kIsReleased(Keyboard::F1)){
		showDebug = !showDebug;
	}
	if (Controls::get()->kIsPressed(sf::Keyboard().Escape)){

		if (state == menu){
			state = exit;
		}
		else{
			state = menu;
		}
	}
}

void StateHandler::handleTime(){

	dt = clock.restart().asSeconds();
	fps = (int)(1 / dt);
	Content::get()->setDebugText(std::to_string(fps));
}

StateHandler::~StateHandler()
{

}
