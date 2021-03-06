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
	bool canClimb, canClimbUp, canClimbDown, isClimbing, doesTouchLadder;
public:
	Player();
	Gun gun;
	void create(float posX, float posY, float sizeX, float sizeY);
	void update(float dt, Map &ptr, sf::View);
	void updateMovement(float dt);
	void jump(float dt);
	void playerHit();
	void checkCollision(Map &ptr, sf::View);
	void fixValuesBasedOnCollision();
	void acceleratePlayerX(float dt);
	void deceleratePlayerX(float dt);
	void updateGun();
	void drawGun();
	sf::RectangleShape getbody();
	sf::Sprite getSprite();

	~Player();
};
#endif;