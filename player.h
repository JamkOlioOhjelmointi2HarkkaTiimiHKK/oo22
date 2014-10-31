#ifndef PLAYER_H
#define PLAYER_H
#include "character.h"
class Player:public Character{
public:
	Player();
	void update();
	void create(float posX, float posY);
	~Player();
};
#endif;