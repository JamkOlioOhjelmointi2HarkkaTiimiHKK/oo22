#include "character.h"

Character::Character(){
	sprite.setPosition(0, 0);
	this->setSize(sf::Vector2f(0,0));
	DX = DY = 0;
}

Character::~Character(){

}

void Character::initializeCharacter(float posX, float posY, float sizeX, float sizeY, bool isPlayer){
	sprite.setPosition(posX, posY);
	this->setSize(sf::Vector2f(sizeX, sizeY));
	this->sizeX = sizeX;
	this->sizeY = sizeY;
	DX = DY = 0;
	velocityX = 0;
	velocityY = 0;
	sprite.setOrigin(sf::Vector2f(sizeX / 2, sizeY / 2));
	falling = false;
	recentlyjumped = false;
	hitbox.initializeHitBoxes(sprite, sizeX, sizeY, isPlayer);
}

void Character::move(float dt){
	sprite.setPosition(sprite.getPosition().x + (DX * (velocityX * dt)), sprite.getPosition().y + (DY * (velocityY * dt)));
}

void Character::draw(){
	window.draw(sprite);
}
void Character::drawHitboxes(){
	hitbox.draw();
}

void Character::createCharacter(sf::Vector2f position, sf::Vector2f size, bool isPlayer){
	initializeCharacter(position.x, position.y, size.x, size.y, isPlayer);
}
void Character::createCharacter(float posX, float posY, float sizeX, float sizeY, bool isPlayer){
	initializeCharacter(posX, posY, sizeX, sizeY, isPlayer);
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
void Character::applyGravity(){
	if (falling){
		if (this->DY == -1)
			this->velocityY -= 50;
		if (this->velocityY <= 0)
			this->setDY(1);
		if (this->DY == 1 && this->velocityY < 500)
			this->velocityY += 50;
	}
}
void Character::setDX(int dx){
	this->DX = dx;
}

void Character::setDY(int dy){
	this->DY = dy;
}
