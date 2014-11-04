#include "player.h"

Player::Player(){
	
}

void Player::update(float dt){
	
	if ((Controls::get()->iskeydown(sf::Keyboard::A)) && (Controls::get()->iskeydown(sf::Keyboard::D))){
		this->setDX(0);
	}
	else if (Controls::get()->iskeydown(sf::Keyboard::A)){
		this->setDX(-1);
	}
	else if (Controls::get()->iskeydown(sf::Keyboard::D)){
		this->setDX(1);
	}
	else{
		this->setDX(0);
	}


	this->move(dt);
	
}

void Player::create(float posX, float posY){
	this->createCharacter(posX, posY);
	this->setTexture(&Content::get()->playerTexture);
}
Player::~Player(){

}