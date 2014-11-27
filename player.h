#ifndef PLAYER_H
#define PLAYER_H
#include "character.h"
#include "Controls.h"
class Player:public Character{
public:
	Player();
	float jumpstart;
	void update(float dt);
	void create(float posX, float posY, float sizeX, float sizeY);
	~Player();
};
#endif;