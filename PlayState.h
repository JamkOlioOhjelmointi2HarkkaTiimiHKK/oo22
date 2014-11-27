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
	Enemy enemy;
	Map map;
	Map *mapPtr;
	Clock clock, secondClock;
	Time elapsedTime;
	bool showDebug, playModeIsActive, exitToMenu, secondPassed;
	int fps;
	float dt;
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