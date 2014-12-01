#ifndef ENEMY_H
#define ENEMY_H
#include "character.h"
#include "Controls.h"
class Enemy :public Character{
public:
	Enemy();
	float sizeX, sizeY;
	int type;
	void update(float dt, float playerposX, float playerposY);
	void create(float posX, float posY, int type);
	~Enemy();
};
#endif;