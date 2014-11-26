#include "StateHandler.h"

StateHandler::StateHandler()
{
	state = uninitialized;

	editState = new EditorState();

	ifstream lahde(OPTIONS_FILENAME, ios_base::binary);
	
	showDebug = true;

	if (!lahde.is_open()){
		cout << "Options tiedostoa ei loytynyt!" << endl << "Ladataan default asetukset" << endl;
		optionsStruct.settings.antialiasingLevel = 0;
		optionsStruct.isVsync = true;
		optionsStruct.fpsLimit = 0;
		optionsStruct.isFullScreen = false;
		ofstream kohde(OPTIONS_FILENAME, ios_base::binary|ios_base::out);
		if (!kohde.is_open()){
			cout << "Tiedoston luominenkaan ei onnistunut!" << endl;
		}
		kohde.write((char *)&optionsStruct, sizeof(optionValues));
		kohde.close();
	}
	lahde.read((char*)&optionsStruct, sizeof(optionValues));
	lahde.close();
	if (optionsStruct.isFullScreen)
		window.create(VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "OO22", Style::Fullscreen, optionsStruct.settings);
	else
		window.create(VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "OO22", Style::Default, optionsStruct.settings);
	window.setVerticalSyncEnabled(optionsStruct.isVsync);
	window.setFramerateLimit(optionsStruct.fpsLimit);
	elapsedTime = secondClock.restart();
	fps = 0;
	titleAnimation = 0;
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
			PlayState playMode;
			if (playMode.runPlayState(window))
				state = menu;
			else
				state = exit;
			break;
		}
		case edit:
		{
			editState->loop();
				if (Controls::get()->kIsPressed(sf::Keyboard().Escape))
				{
					state = menu;
				}
				break;
		}
		case mergeState:
			merge = new Merge();
			merge->loop();
			if (Controls::get()->kIsPressed(sf::Keyboard().Escape))
			{
				state = menu;
			}
			break;
	}
	
}

#pragma region Menu
void StateHandler::runMenu()
{
	initializeMenu();
	
	while (state == menu){
		
		elapsedTime = secondClock.getElapsedTime();
		handleControls(window);
		updateMenu();
		drawMenu(window);
		handleTime();
	}
}

void StateHandler::updateMenu(){

	for (int i = 0; i < buttons.size(); ++i)
	{
		buttons[i]->update();
	}
	if (titleAnimation < 255){
		titleAnimation += (4 * dt);
		title.setColor(Color(255, 255, 255, titleAnimation));
	}
	
}

void StateHandler::drawMenu(RenderWindow &window){
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
void StateHandler::initializeMenu(){
	Vector2f menuButtonSize(Vector2f(150, 85));
	title.setFont(Content::get()->calibri);
	title.setCharacterSize(400);
	title.setString("OO22");
	title.setPosition(10, -100);
	
	buttons.push_back(new Button(Vector2f(35, 400), [&](){state = play; }, menuButtonSize, "Play"));
	buttons.push_back(new Button(Vector2f(35, 500), [&](){state = options; }, menuButtonSize, "Options"));
	buttons.push_back(new Button(Vector2f(35, 600), [&](){state = exit; }, menuButtonSize, "Exit"));

	buttons.push_back(new Button(menuButtonSize, sf::Vector2f(200, 500), "Edit", [&]()
	{
		state = edit;
	}));

	buttons.push_back(new Button(menuButtonSize, sf::Vector2f(200, 600), "merge", [&]()
	{
		state = mergeState;
	}));
}
#pragma endregion Menu

#pragma region Options
void StateHandler::runOptions(){

	initializeOptions();

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
	antiAliasingButton.update();
	fullScreenButton.update();
	if (titleAnimation < 255){
		titleAnimation += (4 * dt);
		title.setColor(Color(255, 255, 255, titleAnimation));
	}
}

void StateHandler::drawOptions(RenderWindow &window){
	window.clear(Color::Black);
	if (showDebug){
		window.draw(Content::get()->debugText);
	}
	window.draw(title);
	backButton.draw(window);
	applyButton.draw(window);
	vsyncButton.draw(window);
	fpsLimitButton.draw(window);
	antiAliasingButton.draw(window);
	fullScreenButton.draw(window);
	window.display();
}

void StateHandler::initializeOptions(){
	Vector2f optionsButtonSize(Vector2f(150, 85));
	Vector2f optionsWideButtonSize(Vector2f(250, 85));
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

	backButton.initialize(Vector2f(35, 600), [&](){state = menu; }, optionsButtonSize, "Back");
	applyButton.initialize(Vector2f(35, 500), [&](){applyOptionSettings(); }, optionsButtonSize, "Apply");
	vsyncButton.initialize(Vector2f(200, 500), [&](){changeVsync(); }, optionsWideButtonSize, vsyncButtonString);
	fpsLimitButton.initialize(Vector2f(200, 600), [&](){changeFPSLimit(); }, optionsWideButtonSize, fpsLimitString);
	antiAliasingButton.initialize(Vector2f(200, 400), [&](){changeAA(); }, optionsWideButtonSize, AAString);
	fullScreenButton.initialize(Vector2f(465, 600), [&](){changeFullScreen(); }, optionsWideButtonSize, fullScreenString);
}

void StateHandler::applyOptionSettings(){
	window.setVerticalSyncEnabled(optionsStruct.isVsync);
	window.setFramerateLimit(optionsStruct.fpsLimit);

	if (optionsStruct.isFullScreen)
		window.create(VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "OO22", Style::Fullscreen, optionsStruct.settings);
	else
		window.create(VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "OO22", Style::Default, optionsStruct.settings);

	ofstream kohde(OPTIONS_FILENAME, ios_base::binary | ios_base::out);
	if (!kohde.is_open()){
		cout << "Options tietojen tallennus ei onnistunut!" << endl;
	}
	kohde.write((char *)&optionsStruct, sizeof(optionValues));
	kohde.close();
}

void StateHandler::changeVsync(){

	std::string vsyncButtonString;

	optionsStruct.isVsync = !optionsStruct.isVsync;

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
void StateHandler::changeAA(){
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
	antiAliasingButton.buttonText.setString(AAString);
}
void StateHandler::changeFullScreen(){

	std::string fullScreenString;

	optionsStruct.isFullScreen = !optionsStruct.isFullScreen;

	if (optionsStruct.isFullScreen)
		fullScreenString = "Fullscreen";
	else
		fullScreenString = "Windowed";
	fullScreenButton.buttonText.setString(fullScreenString);
}
#pragma endregion Options

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
	delete merge;
	delete editState;
}