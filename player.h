#ifndef PLAYER_H
#define PLAYER_H
#include "character.h"
#include "Controls.h"
#include "Map.h"
#include "Utility.h"
class Player:public Character{
private:
	float jumpstart;
public:
	Player();
	void create(float posX, float posY, float sizeX, float sizeY);
	void update(float dt, Map &ptr, sf::View);
	void updateMovement();
	void jump();
	void applyGravity();
	void checkLegCollision(Map &ptr,sf::View);
	void checkBodyCollision(Map &ptr, sf::View);

	int halfScreenX = SCREEN_WIDTH / 2;
	int halfscreenY = SCREEN_HEIGHT / 2;
	~Player();
};
#endif;