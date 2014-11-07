#include "Play.h"

Play::Play(){
	playModeIsActive = true;
	exitToMenu = true;
	fps = 0;
}
Play::~Play(){

}
bool Play::runPlay(RenderWindow &window)
{
	initializePlay();

	while (playModeIsActive){
		elapsedTime = secondClock.getElapsedTime();
		handleControls(window);
		updatePlay();
		drawPlay(window);
		handleTime();
	}
	return exitToMenu;
}

void Play::initializePlay(){
	player.create(200, 200, 32, 64);
}

void Play::updatePlay(){
	player.update(dt);
	//cout << player.getPosition().x << ", " << dt << endl;
}

void Play::drawPlay(RenderWindow &window){
	window.clear(Color::Black);
	if (showDebug){
		window.draw(Content::get()->debugText);
	}
	player.draw(window);
	window.display();

}

void Play::handleControls(RenderWindow &window){

	Controls::get()->update(window);
	if (Controls::get()->kIsReleased(Keyboard::F1)){
		showDebug = !showDebug;
	}
	if (Controls::get()->kIsPressed(sf::Keyboard().Escape)){
		playModeIsActive = false;
	}

	Event currentEvent;
	if (window.pollEvent(currentEvent))
	{
		if (currentEvent.type == Event::Closed){
			playModeIsActive = false;
			exitToMenu = false;
		}
	}
}

void Play::handleTime(){

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