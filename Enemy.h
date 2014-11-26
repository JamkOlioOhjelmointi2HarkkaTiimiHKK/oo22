#ifndef ENEMY_H
#define ENEMY_H
#include "character.h"
#include "Controls.h"
class Enemy :public Character{
public:
	Enemy();
	void update(float dt);
	void create(float posX, float posY, float sizeX, float sizeY);
	~Enemy();
};
#endif;