#include "player.h"

Player::Player(){
	
}

void Player::update(){

}

void Player::create(float posX, float posY){
	this->createCharacter(posX, posY);
	this->setTexture(&Content::get()->playerTexture);
}
Player::~Player(){

}