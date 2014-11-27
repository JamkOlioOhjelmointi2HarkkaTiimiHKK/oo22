#include "player.h"

Player::Player(){
	
}

void Player::create(float posX, float posY, float sizeX, float sizeY){
	this->createCharacter(posX, posY, sizeX, sizeY);
	this->sprite.setTexture(Content::get()->playerTexture);
}
void Player::update(float dt, Map &ptr){
	
	updateMovement();

	applyGravity();
	
	checkCollision(ptr);

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

void Player::checkCollision(Map &ptr){
	if (sprite.getPosition().y >= 400){
		falling = false;
		this->setDY(0);
		this->velocityY = 0;
		recentlyjumped = false;
		sprite.setPosition(sprite.getPosition().x, 390);
	}

	

}
Player::~Player(){

}