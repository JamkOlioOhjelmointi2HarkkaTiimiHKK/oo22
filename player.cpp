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
		if (!recentlyjumped){
			if (this->DY == 0){
				if (this->velocityY == 0)
					this->setDY(-1);
				falling = true;
			}
			if (this->velocityY < 500 && this->DY == -1){
				this->velocityY = this->velocityY + 50;

			}
			if (velocityY == 500)
				recentlyjumped = true;
		}
		
	}
		//if (Controls::get()->kIsReleased(sf::Keyboard::Space)){
	if (falling && !Controls::get()->iskeydown(sf::Keyboard::Space)){
				if (this->DY == -1)
				this->velocityY = this->velocityY - 50;
				if (this->velocityY==0)
				this->setDY(1);
				if (this->DY == 1 && this->velocityY < 500)
					this->velocityY = this->velocityY + 50;

			}
		//}
	
	if (sprite.getPosition().y >= 400){
		falling = false;
		this->setDY(0);
		this->velocityY = 0;
		recentlyjumped = false;
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