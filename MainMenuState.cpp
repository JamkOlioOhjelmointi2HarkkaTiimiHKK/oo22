#include "MainMenuState.h"

MainMenuState::MainMenuState(){
	menuModeIsActive = true;
	showDebug = true;
	state = menu;

	std::ifstream lahde(OPTIONS_FILENAME, std::ios_base::binary);
	
	if (!lahde.is_open()){
		std::cout << "Options tiedostoa ei loytynyt!" << std::endl << "Ladataan default asetukset" << std::endl;
		optionsStruct.settings.antialiasingLevel = 0;
		optionsStruct.isVsync = true;
		optionsStruct.fpsLimit = 0;
		optionsStruct.isFullScreen = false;
		std::ofstream kohde(OPTIONS_FILENAME, std::ios_base::binary | std::ios_base::out);
		if (!kohde.is_open()){
			std::cout << "Tiedoston luominenkaan ei onnistunut!" << std::endl;
		}
		kohde.write((char *)&optionsStruct, sizeof(OptionValues));
		kohde.close();
	}
	lahde.read((char*)&optionsStruct, sizeof(OptionValues));
	lahde.close();
	if (optionsStruct.isFullScreen)
		window.create(VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "OO22", Style::Fullscreen, optionsStruct.settings);
	else
		window.create(VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "OO22", Style::Default, optionsStruct.settings);
	window.setVerticalSyncEnabled(optionsStruct.isVsync);
	window.setFramerateLimit(optionsStruct.fpsLimit);

	fps = 0;
	titleAnimation = 0;

	Vector2f menuButtonSize(Vector2f(150, 85));
	Vector2f optionsButtonSize(Vector2f(150, 85));
	Vector2f optionsWideButtonSize(Vector2f(250, 85));

	title.setFont(Content::get()->calibri);
	title.setCharacterSize(400);
	title.setString("OO22");
	title.setPosition(10, -100);

	std::string vsyncButtonString, fpsLimitString, AAString, fullScreenString;
	
	if (optionsStruct.isVsync)
		vsyncButtonString = "vsync: ON";
	else
		vsyncButtonString = "vsync: OFF";
	if (optionsStruct.fpsLimit != 0)
		fpsLimitString = "FPS limit: " + std::to_string(optionsStruct.fpsLimit);
	else
		fpsLimitString = "FPS limit: Unlimited";

	AAString = "AA: " + std::to_string(optionsStruct.settings.antialiasingLevel);

	if (optionsStruct.isFullScreen)
		fullScreenString = "Fullscreen";
	else
		fullScreenString = "Windowed";

	menuButtons.push_back(new Button(Vector2f(35, 400), [&](){state = play; menuModeIsActive = false; }, menuButtonSize, "Play"));
	menuButtons.push_back(new Button(Vector2f(35, 500), [&](){showOptions = true; }, menuButtonSize, "Options"));
	menuButtons.push_back(new Button(Vector2f(35, 600), [&](){state = exit; menuModeIsActive = false; }, menuButtonSize, "Exit"));
	menuButtons.push_back(new Button(menuButtonSize, sf::Vector2f(200, 500), "Edit", [&](){state = edit; menuModeIsActive = false; }));
	menuButtons.push_back(new Button(menuButtonSize, sf::Vector2f(200, 600), "merge", [&](){state = mergeState; menuModeIsActive = false; }));

	optionButtons.push_back(new Button(Vector2f(35, 600), [&](){state = menu; showOptions = false; }, optionsButtonSize, "Back"));
	optionButtons.push_back(new Button(Vector2f(35, 500), [&](){applyOptionSettings(); }, optionsButtonSize, "Apply"));
	optionButtons.push_back(new Button(Vector2f(200, 500), [&](){changeVsync(); }, optionsWideButtonSize, vsyncButtonString));
	optionButtons.push_back(new Button(Vector2f(200, 600), [&](){changeFPSLimit(); }, optionsWideButtonSize, fpsLimitString));
	optionButtons.push_back(new Button(Vector2f(200, 400), [&](){changeAA(); }, optionsWideButtonSize, AAString));
	optionButtons.push_back(new Button(Vector2f(465, 600), [&](){changeFullScreen(); }, optionsWideButtonSize, fullScreenString));
}
MainMenuState::~MainMenuState(){

}

void MainMenuState::runMainMenuState(){
	while (menuModeIsActive){
		elapsedTime = secondClock.getElapsedTime();
		handleControls();
		if (showOptions){
			updateOptionsMenuState();
			drawOptionsMenuState();
		}
		else{
			updateMainMenuState();
			drawMainMenuState();
		}

		handleTime();
	}
}   

void MainMenuState::updateMainMenuState(){
	for (int i = 0; i < menuButtons.size(); ++i)
	{
		menuButtons[i]->update();
	}
	if (showDebug){
		Content::get()->setDebugTextPosition(0, 0);
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

	for (int i = 0; i < menuButtons.size(); ++i)
	{
		menuButtons[i]->draw();
	}
	window.display();
}

void MainMenuState::updateOptionsMenuState(){
	for (int i = 0; i < optionButtons.size(); ++i)
	{
		optionButtons[i]->update();
	}
	if (titleAnimation < 255){
		titleAnimation += (4 * dt);
		title.setColor(Color(255, 255, 255, titleAnimation));
	}
}

void MainMenuState::drawOptionsMenuState(){
	window.clear(Color::Black);
	if (showDebug){
		window.draw(Content::get()->debugText);
	}
	window.draw(title);
	for (int i = 0; i < optionButtons.size(); ++i)
	{
		optionButtons[i]->draw();
	}
	window.display();
}

void MainMenuState::changeVsync(){

	std::string vsyncButtonString;

	optionsStruct.isVsync = !optionsStruct.isVsync;

	if (optionsStruct.isVsync)
		vsyncButtonString = "vsync: ON";
	else
		vsyncButtonString = "vsync: OFF";

	optionButtons[2]->buttonText.setString(vsyncButtonString);
}

void MainMenuState::changeFPSLimit(){

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
		fpsLimitString = "FPS limit: No cap";

	optionButtons[3]->buttonText.setString(fpsLimitString);
}
void MainMenuState::changeAA(){
	std::string AAString;

	if (optionsStruct.settings.antialiasingLevel > 0){
		if (optionsStruct.settings.antialiasingLevel >= 16){
			optionsStruct.settings.antialiasingLevel = 0;
		}
		else{
			optionsStruct.settings.antialiasingLevel *= 2;
		}
	}
	else{
		optionsStruct.settings.antialiasingLevel = 2;
	}
	AAString = "AA: " + std::to_string(optionsStruct.settings.antialiasingLevel);
	optionButtons[4]->buttonText.setString(AAString);
}
void MainMenuState::changeFullScreen(){

	std::string fullScreenString;

	optionsStruct.isFullScreen = !optionsStruct.isFullScreen;

	if (optionsStruct.isFullScreen)
		fullScreenString = "Fullscreen";
	else
		fullScreenString = "Windowed";
	optionButtons[5]->buttonText.setString(fullScreenString);
}

void MainMenuState::applyOptionSettings(){
	window.setVerticalSyncEnabled(optionsStruct.isVsync);
	window.setFramerateLimit(optionsStruct.fpsLimit);

	if (optionsStruct.isFullScreen)
		window.create(VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "OO22", Style::Fullscreen, optionsStruct.settings);
	else
		window.create(VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "OO22", Style::Default, optionsStruct.settings);

	std::ofstream kohde(OPTIONS_FILENAME, std::ios_base::binary | std::ios_base::out);
	if (!kohde.is_open()){
		std::cout << "Options tietojen tallennus ei onnistunut!" << std::endl;
	}
	kohde.write((char *)&optionsStruct, sizeof(OptionValues));
	kohde.close();

	state = menu;
	showOptions = false;
}

void MainMenuState::handleControls(){

	Controls::get()->update(window);
	if (Controls::get()->kIsReleased(Keyboard::F1)){
		showDebug = !showDebug;
	}
	if (Controls::get()->kIsPressed(sf::Keyboard().Escape) && showOptions){
		showOptions = false;
	}
	else if (Controls::get()->kIsPressed(sf::Keyboard().Escape) && !showOptions){
		menuModeIsActive = false;
		state = exit;
	}

	Event currentEvent;
	if (window.pollEvent(currentEvent))
	{
		if (currentEvent.type == Event::Closed){
			menuModeIsActive = false;
			state = exit;
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