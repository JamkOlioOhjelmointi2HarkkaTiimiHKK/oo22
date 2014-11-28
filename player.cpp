#include "player.h"

Player::Player(){
	
}

void Player::create(float posX, float posY, float sizeX, float sizeY){
	this->createCharacter(posX, posY, sizeX, sizeY);
	this->sprite.setTexture(Content::get()->playerTexture);
}
void Player::update(float dt, Map &ptr){
	
	checkLegCollision(ptr);
	updateMovement();
	checkBodyCollision(ptr);
	applyGravity();
	this->move(dt);
	hitbox.update(sprite);
}
void Player::updateMovement(){
	if ((Controls::get()->iskeydown(sf::Keyboard::A)) && (Controls::get()->iskeydown(sf::Keyboard::D))){
		this->setDX(0);
	}
	else if (Controls::get()->iskeydown(sf::Keyboard::A)){
		this->setDX(-1);
		this->setFacingDirection(false);
	}
	else if (Controls::get()->iskeydown(sf::Keyboard::D)){
		this->setDX(1);
		this->setFacingDirection(true);
	}
	else{
		this->setDX(0);
	}


	if (Controls::get()->iskeydown(sf::Keyboard::Space)){
		jump();
	}
}

void Player::jump(){
	if (!falling){
		jumpstart = sprite.getPosition().y;
	}

	if (this->DY == 0){
		if (this->velocityY == 0){
			this->setDY(-1);

		}
		falling = true;
	}
	if (!recentlyjumped){
		if (this->velocityY < 500 && this->DY == -1){
			this->velocityY = 500;
		}
	}
	if ((jumpstart - sprite.getPosition().y > 100)){
		recentlyjumped = true;
	}
}

void Player::applyGravity(){
	if (falling){
		if (this->DY == -1)
			this->velocityY = this->velocityY - 50;
		if (this->velocityY == 0)
			this->setDY(1);
		if (this->DY == 1 && this->velocityY < 500)
			this->velocityY = this->velocityY + 50;
	}
}

void Player::checkLegCollision(Map &ptr){
	for (int i = 0; i < ptr.mapObjects.size(); i++){
		if (Utility::boxHit(this->hitbox.legHitbox, ptr.mapObjects[i]->shape)){
			falling = false;
			this->setDY(0);
			this->velocityY = 0;
			recentlyjumped = false;
			sprite.setPosition(sprite.getPosition().x, ptr.mapObjects[i]->getPos().y - this->sizeY / 2 + 1);
			this->legHitbocCollides = true;
		}
	}
	if (!this->legHitbocCollides){
		falling = true;
	}

	this->legHitbocCollides = false;

}
void Player::checkBodyCollision(Map &ptr){
	for (int i = 0; i < ptr.mapObjects.size(); i++){

		if (Utility::boxHit(this->hitbox.bodyLeftHitbox, ptr.mapObjects[i]->shape)){
			this->velocityX = 0;
			sprite.setPosition(ptr.mapObjects[i]->getPos().x + ptr.mapObjects[i]->getSize().x + this->sizeX / 2 - 1, sprite.getPosition().y);
			this->bodyLeftHitbocCollides = true;
		}

		if (Utility::boxHit(this->hitbox.bodyRightHitbox, ptr.mapObjects[i]->shape)){
			this->velocityX = 0;
			sprite.setPosition(ptr.mapObjects[i]->getPos().x - this->sizeX / 2 + 1, sprite.getPosition().y);
			this->bodyRightHitbocCollides = true;
		}
	}

	if ((!this->bodyLeftHitbocCollides || this->DX != -1) && (!this->bodyRightHitbocCollides || this->DX != 1)){
		this->velocityX = 500;
	}

	this->bodyLeftHitbocCollides = false;
	this->bodyRightHitbocCollides = false;
}
Player::~Player(){

}