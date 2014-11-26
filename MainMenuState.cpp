#include "MainMenuState.h"

MainMenuState::MainMenuState(){
	menuModeIsActive = true;
	startPlayState = false;
	fps = 0;
	titleAnimation = 0;

	Vector2f menuButtonSize(Vector2f(150, 85));
	title.setFont(Content::get()->calibri);
	title.setCharacterSize(400);
	title.setString("OO22");
	title.setPosition(10, -100);

	buttons.push_back(new Button(Vector2f(35, 400), [&](){startPlayState = true; }, menuButtonSize, "Play"));
	buttons.push_back(new Button(Vector2f(35, 500), [&](){showOptions = true; }, menuButtonSize, "Options"));
	//buttons.push_back(new Button(Vector2f(35, 600), [&](){state = exit; }, menuButtonSize, "Exit"));

	buttons.push_back(new Button(menuButtonSize, sf::Vector2f(200, 500), "Edit", [&]()
	{
		//state = edit;
	}));

	buttons.push_back(new Button(menuButtonSize, sf::Vector2f(200, 600), "merge", [&]()
	{
		//state = mergeState;
	}));
}
MainMenuState::~MainMenuState(){

}

bool MainMenuState::runMainMenuState(){
	initializeMainMenuState();

	while (menuModeIsActive){
		elapsedTime = secondClock.getElapsedTime();
		handleControls();
		if (showOptions){
			
		}
		else{
			updateMainMenuState();
			drawMainMenuState();
		}
		
		handleTime();
	}
	return startPlayState;
}   

void MainMenuState::updateMainMenuState(){
	for (int i = 0; i < buttons.size(); ++i)
	{
		buttons[i]->update();
	}
	if (titleAnimation < 255){
		titleAnimation += (4 * dt);
		title.setColor(Color(255, 255, 255, titleAnimation));
	}
}

void MainMenuState::drawMainMenuState(){
	window.clear(Color::Black);
	if (showDebug){
		window.draw(Content::get()->debugText);
	}
	window.draw(title);

	for (int i = 0; i < buttons.size(); ++i)
	{
		buttons[i]->draw();
	}
	window.display();
}

void MainMenuState::handleControls(){

	Controls::get()->update(window);
	if (Controls::get()->kIsReleased(Keyboard::F1)){
		showDebug = !showDebug;
	}
	if (Controls::get()->kIsPressed(sf::Keyboard().Escape)){
		menuModeIsActive = false;
	}

	Event currentEvent;
	if (window.pollEvent(currentEvent))
	{
		if (currentEvent.type == Event::Closed){
			menuModeIsActive = false;
		}
	}
}

void MainMenuState::handleTime(){

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