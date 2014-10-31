#include "StateHandler.h"


StateHandler::StateHandler()
{
	state = uninitialized;
	window.create(VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "OO22");
	window.setVerticalSyncEnabled(true);
	showDebug = true;
	elapsedTime = secondClock.restart();
	fps = 0;
}

void StateHandler::startGame()
{
	if (state != uninitialized)
		return;
	state = menu;

	while (!exitGame())
	{			
		gameLoop();
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

void StateHandler::gameLoop()
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
	Button playButton(Vector2f(SCREEN_WIDTH - 200, 300), "Play", [&](){state = play; });
	Button exitButton(Vector2f(SCREEN_WIDTH - 200, 500), "Exit", [&](){state = exit; });

	while (state == menu){
		
		elapsedTime = secondClock.getElapsedTime();

		handleControls(window);
		playButton.update();
		exitButton.update();

		window.clear(Color::Black);
		if (showDebug){
			window.draw(Content::get()->debugText); 
		}

		playButton.draw(window);
		exitButton.draw(window);
		window.display();

		handleTime();
	}
	
}

void StateHandler::runPlay()
{	
	//player.create(200, 200);

	while (state == play){

		handleControls(window);

		window.clear(Color::Black);
		if (showDebug){
			window.draw(Content::get()->debugText);
		}
		window.display();

		handleTime();
	}
}

void StateHandler::handleControls(RenderWindow &window){
	
	Controls::get()->update(window);
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

	Event currentEvent;
	if (window.pollEvent(currentEvent))
	{
		if (currentEvent.type == Event::Closed)
			state = exit;

	}
}

void StateHandler::handleTime(){

	dt = clock.restart().asSeconds();

	if (elapsedTime.asMilliseconds() >= 1000){
		secondClock.restart();
		secondPassed = true;
		Content::get()->setDebugText(std::to_string(fps));
		fps = 0;
	}
	else{
		fps++;
		secondPassed = false;
	}
}

void StateHandler::setState(gameState s){
	this->state = s;
}

StateHandler::~StateHandler()
{

}
