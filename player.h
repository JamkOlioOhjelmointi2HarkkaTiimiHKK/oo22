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
	void checkCollision(Map &ptr, sf::View);
	void fixValuesBasedOnCollision();
	void acceleratePlayerX();
	void deceleratePlayerX();

	sf::Sprite getSprite();

	~Player();
};
#endif;