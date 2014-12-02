#ifndef PLAYER_H
#define PLAYER_H
#include "character.h"
#include "Controls.h"
#include "Map.h"
#include "Utility.h"
#include "Gun.h"
class Player:public Character{
private:
	float jumpstart;
public:
	Player();
	Gun gun;
	void create(float posX, float posY, float sizeX, float sizeY);
	void update(float dt, Map &ptr, sf::View);
	void updateMovement();
	void jump();
	void applyGravity();
	void checkCollision(Map &ptr, sf::View);
	void acceleratePlayerX();
	void deceleratePlayerX();

	sf::Sprite getSprite();

	int halfscreenY = SCREEN_HEIGHT / 2;
	int halfScreenX = SCREEN_WIDTH / 2;

	~Player();
};
#endif;