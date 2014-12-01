#include "Enemy.h"

Enemy::Enemy(){

}

void Enemy::update(float dt,float playerposX, float playerposY){
	switch (type){
	case 0:
		
		this->move(dt);
		hitbox.update(sprite);
		break;
	case 1:
		velocityX = velocityY = 100;
		if (playerposX < sprite.getPosition().x){
			this->setDX(-1);
		}
		else{
			this->setDX(1);
		}
		if (playerposY < sprite.getPosition().y){
			this->setDY(-1);
		}
		else{
			this->setDY(1);
		}
		this->move(dt);
		hitbox.update(sprite);
		break;
	default:
		break;
	}
	
}

void Enemy::create(float posX, float posY, int type){
	this->type = type;
	switch (type){
	case 0:
		sizeX = 32;
		sizeY = 64;
		this->createCharacter(posX, posY, sizeX, sizeY, false);
		this->sprite.setTexture(Content::get()->janisTexture);
		break;
	case 1:
		sizeX = 40;
		sizeY = 40;
		this->createCharacter(posX, posY, sizeX, sizeY, false);
		this->sprite.setTexture(Content::get()->ghostTexture);
		break;
	default:
		break;
	}
	/*this->createCharacter(posX, posY, sizeX, sizeY);
	
	this->sprite.setTexture(Content::get()->enemyTexture);*/
	//this->setTexture(&Content::get()->playerTexture);
}
Enemy::~Enemy(){
	
}