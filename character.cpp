#include "character.h"

Character::Character(){
	this->setPosition(0, 0);
	this->setSize(sf::Vector2f(0,0));
	DX = DY = 0;
}

Character::~Character(){

}

void Character::move(float dt){
	this->setPosition(this->getPosition().x + (DX * (velocityX * dt)), this->getPosition().y + (DY * (velocityY * dt)));
}

void Character::draw(sf::RenderWindow &window){
	window.draw(*this);
}

void Character::createCharacter(float posX, float posY){
	this->setPosition(posX, posY);
	this->setSize(sf::Vector2f(150, 400));
	DX = DY = 0;
	velocityX = velocityY = 500;
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