#include "PlayState.h"

PlayState::PlayState(){
	playModeIsActive = true;
	showDebug = true;
	exitToMenu = true;
	fps = 0;
	mapPtr = &map;

	view.reset(sf::FloatRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT));
	window.setView(view);
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
	player.create(350, 350, 32, 64);
	enemy1.create(400, 400, 0);
	enemy2.create(600, 400, 1);
}

void PlayState::updatePlayState(){
	player.update(dt, *mapPtr,view);

	view.reset(sf::FloatRect(player.getSprite().getPosition().x - halfScreenX, player.getSprite().getPosition().y - halfscreenY, SCREEN_WIDTH, SCREEN_HEIGHT));
	window.setView(view);
	if (showDebug){
		Content::get()->setDebugTextPosition(view.getCenter().x - halfScreenX, view.getCenter().y - halfscreenY);
	}
	enemy1.update(dt);
	enemy2.update(dt);
	map.update();
}

void PlayState::drawPlayState(){
	window.clear(Color::Black);

	player.draw();
	if (showDebug){
		window.draw(Content::get()->debugText);
		player.drawHitboxes();
	}
	enemy1.draw();
	enemy2.draw();
	map.draw(view);
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