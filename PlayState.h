#pragma once
#include <SFML\Graphics.hpp>
#include "StateHandler.h"
#include "player.h"
#include "Enemy.h"
#include "Map.h"
#include <list>
using namespace sf;

class PlayState
{
private:
	
	std::list<Enemy*> enemyList;
	std::list<Enemy*>::iterator listIter;
	Player player;
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

	void spawnEnemy();
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