#include "PlayState.h"

PlayState::PlayState(){
	playModeIsActive = true;
	exitToMenu = true;
	fps = 0;
}
PlayState::~PlayState(){

}
bool PlayState::runPlayState()
{
	initializePlayState();

	while (playModeIsActive){
		elapsedTime = secondClock.getElapsedTime();
		handleControls();
		updatePlayState();
		drawPlayState();
		handleTime();
	}
	return exitToMenu;
}

void PlayState::initializePlayState(){
	player.create(200, 200, 32, 64);
	enemy.create(400, 400, 32, 64);
}

void PlayState::updatePlayState(){
	player.update(dt);
	enemy.update(dt);
	//cout << player.getPosition().x << ", " << dt << endl;
}

void PlayState::drawPlayState(){
	window.clear(Color::Black);

	player.draw(window);
	if (showDebug){
		window.draw(Content::get()->debugText);
		player.drawHitboxes(window);
	}
	enemy.draw(window);
	
	window.display();

}

void PlayState::handleControls(){

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

void PlayState::handleTime(){

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