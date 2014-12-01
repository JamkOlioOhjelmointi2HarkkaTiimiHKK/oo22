#pragma once
#include <SFML\Graphics.hpp>
#include "StateHandler.h"
#include "player.h"
#include "Enemy.h"
#include "Map.h"
using namespace sf;

class PlayState
{
private:
	Player player;
	int koko;
	Enemy *enemy = new Enemy[500];
	Map map;
	Map *mapPtr;
	Clock clock, secondClock;
	Time elapsedTime;
	bool showDebug, playModeIsActive, exitToMenu, secondPassed;
	int fps;
	float dt;
	sf::View view;

	int halfscreenY = SCREEN_HEIGHT / 2;
	int halfScreenX = SCREEN_WIDTH / 2;
public:
	PlayState();
	~PlayState();

	bool runPlayState();
	void initializePlayState();
	void updatePlayState();
	void drawPlayState();
	void handleControls();
	void handleTime();
};