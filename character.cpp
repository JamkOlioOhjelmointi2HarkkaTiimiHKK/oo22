#include "character.h"

Character::Character(){
	sprite.setPosition(0, 0);
	this->setSize(sf::Vector2f(0,0));
	DX = DY = 0;
}

Character::~Character(){

}

void Character::move(float dt){
	sprite.setPosition(sprite.getPosition().x + (DX * (velocityX * dt)), sprite.getPosition().y + (DY * (velocityY * dt)));
}

void Character::draw(sf::RenderWindow &window){
	window.draw(sprite);
}
void Character::createCharacter(sf::Vector2f position, sf::Vector2f size){
	initializeCharacter(position.x, position.y, size.x, size.y);
}
void Character::createCharacter(float posX, float posY, float sizeX, float sizeY){
	initializeCharacter(posX, posY, sizeX, sizeY);
}

void Character::initializeCharacter(float posX, float posY, float sizeX, float sizeY){
	sprite.setPosition(posX, posY);
	this->setSize(sf::Vector2f(sizeX, sizeY));
	DX = DY = 0;
	velocityX = velocityY = 500;
	sprite.setOrigin(sf::Vector2f(sizeX/2, sizeY/2));
}

void Character::setDirection(int dx, int dy){
	this->DX = dx;
	this->DY = dy;
}

void Character::setFacingDirection(bool facingLeft){
	if (facingLeft)
		sprite.setScale(1, 1);
	else
		sprite.setScale(-1, 1);
}

void Character::setDX(int dx){
	this->DX = dx;
}

void Character::setDY(int dy){
	this->DY = dy;
}