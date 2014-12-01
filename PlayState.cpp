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
}

void PlayState::updatePlayState(){
	player.update(dt, *mapPtr,view);

	view.reset(sf::FloatRect(player.getSprite().getPosition().x - halfScreenX, player.getSprite().getPosition().y - halfscreenY, SCREEN_WIDTH, SCREEN_HEIGHT));
	window.setView(view);
	if (showDebug){
		Content::get()->setDebugTextPosition(view.getCenter().x - halfScreenX, view.getCenter().y - halfscreenY);
	}
	for (listIter = enemyList.begin(); listIter != enemyList.end(); ++listIter){
		(*listIter)->update(dt, player.getSprite().getPosition().x, player.getSprite().getPosition().y, *mapPtr, view);
	}
	map.update();
}

void PlayState::drawPlayState(){
	window.clear(Color::Black);

	map.draw(view);
	player.draw();
	if (showDebug){
		window.draw(Content::get()->debugText);
		player.drawHitboxes();
	}
	for (listIter = enemyList.begin(); listIter != enemyList.end(); ++listIter){
		(*listIter)->draw();
	}
	
	window.display();
}

void PlayState::spawnEnemy(){
	Enemy* test = new Enemy(Utility::random(0, 2000), Utility::random(0, 1500), Utility::random(0, 2));
	enemyList.push_back(test);
}

void PlayState::handleControls(){

	Controls::get()->update(window);
	if (Controls::get()->kIsReleased(Keyboard::F1)){
		showDebug = !showDebug;
	}
	if (Controls::get()->kIsPressed(Keyboard().F2)){
		spawnEnemy();
	}
	if (Controls::get()->kIsPressed(Keyboard().Escape)){
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