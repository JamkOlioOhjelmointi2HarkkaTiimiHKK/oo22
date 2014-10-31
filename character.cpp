#include "character.h"

Character::Character(){
}

Character::~Character(){

}

void Character::move(){
	this->setPosition(posX + (DX * velocityX), posY + (DY * velocityY));
}

void Character::createCharacter(float posX, float posY){
	this->setPosition(posX, posY);
	DX = DY = 0;
}

void Character::setPosition(float posX, float posY){
	this->posX = posX;
	this->posY = posY;
}

void Character::setDirection(int dx, int dy){
	this->DX = dx;
	this->DY = dy;
}

void Character::setDX(int dx){
	this->DX = dx;
}

void Character::setDY(int dy){
	this->DY = dy;
}