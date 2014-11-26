#include "Enemy.h"

Enemy::Enemy(){

}

void Enemy::update(float dt){

	


	this->move(dt);
	hitbox.update(sprite);
}

void Enemy::create(float posX, float posY, float sizeX, float sizeY){
	this->createCharacter(posX, posY, sizeX, sizeY);
	this->sprite.setTexture(Content::get()->enemyTexture);
	//this->setTexture(&Content::get()->playerTexture);
}
Enemy::~Enemy(){

}