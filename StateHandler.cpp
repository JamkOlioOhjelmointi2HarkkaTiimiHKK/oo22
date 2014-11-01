#include "StateHandler.h"

StateHandler::StateHandler()
{
	state = uninitialized;
	optionsStruct.settings.antialiasingLevel = 0;
	optionsStruct.isVsync = true;
	optionsStruct.fpsLimit = 0;
	optionsStruct.isFullScreen = false;
	showDebug = true;
	if (optionsStruct.isFullScreen)
		window.create(VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "OO22", Style::Fullscreen, optionsStruct.settings);
	else
		window.create(VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "OO22", Style::Default, optionsStruct.settings);
	window.setVerticalSyncEnabled(optionsStruct.isVsync);
	window.setFramerateLimit(optionsStruct.fpsLimit);
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

#pragma region Menu
void StateHandler::runMenu()
{
	Vector2f menuButtonSize(Vector2f(150, 85));
	playButton.initialize(Vector2f(SCREEN_WIDTH - 200, 300), [&](){state = play; }, menuButtonSize, "Play");
	optionsButton.initialize(Vector2f(SCREEN_WIDTH - 200, 400), [&](){state = options; }, menuButtonSize, "Options");
	exitButton.initialize(Vector2f(SCREEN_WIDTH - 200, 500), [&](){state = exit; }, menuButtonSize, "Exit");

	while (state == menu){
		
		elapsedTime = secondClock.getElapsedTime();
		handleControls(window);
		updateMenu();
		drawMenu(window);
		handleTime();
	}
}

void StateHandler::updateMenu(){
	playButton.update();
	optionsButton.update();
	exitButton.update();
}

void StateHandler::drawMenu(RenderWindow &window){
	window.clear(Color::Black);
	if (showDebug){
		window.draw(Content::get()->debugText);
	}
	playButton.draw(window);
	optionsButton.draw(window);
	exitButton.draw(window);
	window.display();
}
#pragma endregion Menu

#pragma region Options
void StateHandler::runOptions(){

	Vector2f optionsButtonSize(Vector2f(150, 85));
	Vector2f optionsWideButtonSize(Vector2f(250, 85));
	std::string vsyncButtonString, fpsLimitString;

	if (optionsStruct.isVsync)
		vsyncButtonString = "vsync: ON";
	else
		vsyncButtonString = "vsync: OFF";
	if (optionsStruct.fpsLimit != 0)
		fpsLimitString = "FPS limit: " + std::to_string(optionsStruct.fpsLimit);
	else
		fpsLimitString = "FPS limit: Unlimited";

	backButton.initialize(Vector2f(SCREEN_WIDTH - 200, 500), [&](){state = menu; }, optionsButtonSize, "Back");
	applyButton.initialize(Vector2f(SCREEN_WIDTH - 200, 400), [&](){applyOptionSettings(); }, optionsButtonSize, "Apply");
	vsyncButton.initialize(Vector2f(SCREEN_WIDTH / 2, 400), [&](){changeVsync(); }, optionsWideButtonSize, vsyncButtonString);
	fpsLimitButton.initialize(Vector2f(SCREEN_WIDTH / 2, 500), [&](){changeFPSLimit(); }, optionsWideButtonSize, fpsLimitString);

	while (state == options){
		elapsedTime = secondClock.getElapsedTime();
		handleControls(window);
		updateOptions();
		drawOptions(window);
		handleTime();
	}
}

void StateHandler::updateOptions(){
	backButton.update();
	applyButton.update();
	vsyncButton.update();
	fpsLimitButton.update();
}

void StateHandler::drawOptions(RenderWindow &window){
	window.clear(Color::Black);
	if (showDebug){
		window.draw(Content::get()->debugText);
	}
	backButton.draw(window);
	applyButton.draw(window);
	vsyncButton.draw(window);
	fpsLimitButton.draw(window);
	window.display();
}

void StateHandler::applyOptionSettings(){
	window.setVerticalSyncEnabled(optionsStruct.isVsync);
	window.setFramerateLimit(optionsStruct.fpsLimit);
}

void StateHandler::changeVsync(){
	optionsStruct.isVsync = !optionsStruct.isVsync;

	std::string vsyncButtonString;

	if (optionsStruct.isVsync)
		vsyncButtonString = "vsync: ON";
	else
		vsyncButtonString = "vsync: OFF";

	vsyncButton.buttonText.setString(vsyncButtonString);
}
void StateHandler::changeFPSLimit(){

	std::string fpsLimitString;

	if (optionsStruct.fpsLimit > 0){
		if (optionsStruct.fpsLimit > 30){
			if (optionsStruct.fpsLimit > 60){
				optionsStruct.fpsLimit = 0;
			}
			else{
				optionsStruct.fpsLimit = 120;
			}
		}
		else{
			optionsStruct.fpsLimit = 60;
		}
	}
	else{
		optionsStruct.fpsLimit = 30;
	}


	if (optionsStruct.fpsLimit != 0)
		fpsLimitString = "FPS limit: " + std::to_string(optionsStruct.fpsLimit);
	else
		fpsLimitString = "FPS limit: Unlimited";

	fpsLimitButton.buttonText.setString(fpsLimitString);
}
#pragma endregion Options

#pragma region Play
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
void StateHandler::updatePlay(){

}

void StateHandler::drawPlay(RenderWindow &window){

}
#pragma endregion Play

#pragma region Tools
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
#pragma endregion Tools
StateHandler::~StateHandler()
{

}