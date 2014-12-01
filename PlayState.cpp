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
	koko = 0;
	player.create(350, 350, 32, 64);
	enemy[koko].create(400, 400, 1);
	koko += 1;
	enemy[koko].create(450, 450, 1);
	koko += 1;


}

void PlayState::updatePlayState(){
	player.update(dt, *mapPtr,view);

	view.reset(sf::FloatRect(player.getSprite().getPosition().x - halfScreenX, player.getSprite().getPosition().y - halfscreenY, SCREEN_WIDTH, SCREEN_HEIGHT));
	window.setView(view);
	if (showDebug){
		Content::get()->setDebugTextPosition(view.getCenter().x - halfScreenX, view.getCenter().y - halfscreenY);
	}
	for (int i = 0; i < koko; i++){
		enemy[i].update(dt, player.getSprite().getPosition().x, player.getSprite().getPosition().y, *mapPtr, view);
	}
	map.update();
}

void PlayState::drawPlayState(){
	window.clear(Color::Black);

	player.draw();
	if (showDebug){
		window.draw(Content::get()->debugText);
		player.drawHitboxes();
	}
	for (int i = 0; i < koko; i++){
		enemy[i].draw();
	}
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