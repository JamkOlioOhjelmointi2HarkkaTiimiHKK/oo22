#pragma once
#include <SFML\Graphics.hpp>
#include "StateHandler.h"
#include "player.h"
using namespace sf;

class Play
{
private:
	Player player;
	Clock clock, secondClock;
	Time elapsedTime;
	bool showDebug, playModeIsActive, exitToMenu, secondPassed;
	int fps;
	float dt;
public:
	Play();
	~Play();

	bool runPlay(RenderWindow &window);
	void initializePlay();
	void updatePlay();
	void drawPlay(RenderWindow &window);
	void handleControls(RenderWindow &window);
	void handleTime();
};