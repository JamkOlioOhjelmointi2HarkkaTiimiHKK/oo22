#include "StateHandler.h"


StateHandler::StateHandler()
{
	state = uninitialized;
	settings.antialiasingLevel = 0;
	window.create(VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "OO22", Style::Default, settings);
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
			runMenu();
			break;
		}
		case options:
		{
			runOptions();
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
	Vector2f menuButtonSize(Vector2f(150, 85));
	Button playButton(Vector2f(SCREEN_WIDTH - 200, 300), "Play", [&](){state = play; }, menuButtonSize);
	Button optionsButton(Vector2f(SCREEN_WIDTH - 200, 400), "Options", [&](){state = options; }, menuButtonSize);
	Button exitButton(Vector2f(SCREEN_WIDTH - 200, 500), "Exit", [&](){state = exit; }, menuButtonSize);

	while (state == menu){
		
		elapsedTime = secondClock.getElapsedTime();

		handleControls(window);
		
		updateMenu(playButton, optionsButton, exitButton);
		drawMenu(window);
		

		handleTime();
	}
	
}

void StateHandler::updateMenu(Button playButton, Button optionsButton, Button exitButton){
	playButton.update();
	optionsButton.update();
	exitButton.update();
}

void StateHandler::drawMenu(RenderWindow &window){
	window.clear(Color::Black);
	if (showDebug){
		window.draw(Content::get()->debugText);
	}

	//playButton.draw(window);
	//optionsButton.draw(window);
	//exitButton.draw(window);
	window.display();
}

void StateHandler::runOptions(){
	while (state == options){

		handleControls(window);

		window.clear(Color::Black);
		if (showDebug){
			window.draw(Content::get()->debugText);
		}
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
