#include "character.h"

Character::Character(){
}

Character::~Character(){

}

void Character::move(){
	this->setPosition(posX + (DX * velocityX), posY + (DY * velocityY));
}

void Character::setPosition(int posX, int posY){
	this->posX = posX;
	this->posY = posY;
}