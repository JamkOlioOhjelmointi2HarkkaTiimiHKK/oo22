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
	void update(float dt, Map &ptr);
	void updateMovement();
	void jump();
	void applyGravity();
	void checkCollision(Map &ptr);
	~Player();
};
#endif;