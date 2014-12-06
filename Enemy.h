#ifndef ENEMY_H
#define ENEMY_H
#include "character.h"
#include "Controls.h"
#include "Map.h"
#include "Utility.h"
class Enemy :public Character{
public:
	float sizeX, sizeY;
	int type;
	int enemySectorX, enemySectorY;
	sf::Vector2f bottom;
	Enemy();
	Enemy(float posX, float posY, int type);
	Enemy(const Enemy &);
	void jump();
	void checkCollision(Map &ptr, sf::View);
	void update(float dt, float playerposX, float playerposY, Map &ptr, sf::View view);
	void updateJanis(float dt, float playerposX, float playerposY);
	void updateGhost(float dt, float playerposX, float playerposY);
	void updateSlime(float dt, float playerposX, float playerposY);
	void updateFox(float dt, float playerposX, float playerposYp);
	void draw(Map &ptr, sf::View view);
	bool isEnemyOnAdjacentSector(Map &ptr, sf::View view);
	void fixValuesBasedOnCollision();
	void create(float posX, float posY, int type);
	~Enemy();
};
#endif;