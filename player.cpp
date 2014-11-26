#include "player.h"

Player::Player(){
	
}

void Player::update(float dt){
	
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
			this->setDY(-1);
			if (velocityY < 500){
				velocityY = velocityY + 100;
				
			}
			falling = true;
		}
		if (Controls::get()->kIsReleased(sf::Keyboard::Space)){
			if (falling){
				if (DY == -1)
				velocityY = velocityY - 100;
				if (velocityY==0)
				this->setDY(1);
				if (DY == 1 && velocityY < 500)
					velocityY = velocityY + 100;

			}
		}
	
	if (sprite.getPosition().y >= 400){
		falling = false;
		this->setDY(0);
		sprite.setPosition(sprite.getPosition().x, 390);
	}
	
	this->move(dt);
	hitbox.update(sprite);
}

void Player::create(float posX, float posY, float sizeX, float sizeY){
	this->createCharacter(posX, posY, sizeX, sizeY);
	this->sprite.setTexture(Content::get()->playerTexture);
	//this->setTexture(&Content::get()->playerTexture);
}
Player::~Player(){

}