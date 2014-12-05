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
	void updateMovement(float dt);
	void jump(float dt);
	void checkCollision(Map &ptr, sf::View);
	void fixValuesBasedOnCollision();
	void acceleratePlayerX(float dt);
	void deceleratePlayerX(float dt);

	sf::Sprite getSprite();

	~Player();
};
#endif;