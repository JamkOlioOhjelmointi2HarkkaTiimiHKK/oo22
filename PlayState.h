#pragma once
#include <SFML\Graphics.hpp>
#include "StateHandler.h"
#include "player.h"
#include "Enemy.h"
using namespace sf;

class PlayState
{
private:
	Player player;
	Enemy enemy;
	Clock clock, secondClock;
	Time elapsedTime;
	bool showDebug, playModeIsActive, exitToMenu, secondPassed;
	int fps;
	float dt;
public:
	PlayState();
	~PlayState();

	bool runPlayState(RenderWindow &window);
	void initializePlayState();
	void updatePlayState();
	void drawPlayState(RenderWindow &window);
	void handleControls(RenderWindow &window);
	void handleTime();
};