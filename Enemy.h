#ifndef ENEMY_H
#define ENEMY_H
#include "character.h"
#include "Controls.h"
#include "Map.h"
#include "Utility.h"
class Enemy :public Character{
public:
	Enemy();
	float sizeX, sizeY;
	int type;
	void jump();
	void applyGravity();
	void checkCollision(Map &ptr, sf::View);
	void update(float dt, float playerposX, float playerposY, Map &ptr, sf::View view);
	void create(float posX, float posY, int type);
	~Enemy();
};
#endif;