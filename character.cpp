#include "character.h"

Character::Character(){
	sprite.setPosition(0, 0);
	this->setSize(sf::Vector2f(0,0));
	DX = DY = 0;
}

Character::~Character(){

}
//Alustetaan hahmo olio
void Character::initializeCharacter(float posX, float posY, float sizeX, float sizeY, bool isPlayer){
	sprite.setPosition(posX, posY);
	this->setSize(sf::Vector2f(sizeX, sizeY));
	this->sizeX = sizeX;
	this->sizeY = sizeY;
	DX = DY = 0;
	velocityX = 0;
	velocityY = 0;
	sprite.setOrigin(sf::Vector2f(sizeX / 2, sizeY / 2));
	enemyCollides = false;
	falling = false;
	recentlyjumped = false;
	hitbox.initializeHitBoxes(sprite, sizeX, sizeY, isPlayer);
}
//liikuttaa hahmoa
void Character::move(float dt){
	sprite.setPosition(sprite.getPosition().x + (DX * (velocityX * dt)), sprite.getPosition().y + (DY * (velocityY * dt)));
}
//Piirtää hahmon
void Character::draw(){
	window.draw(sprite);
}
//Piirtää hahmon hitboxit, jos sillä on niitä.
void Character::drawHitboxes(){
	hitbox.draw();
}

void Character::createCharacter(sf::Vector2f position, sf::Vector2f size, bool isPlayer){
	initializeCharacter(position.x, position.y, size.x, size.y, isPlayer);
}
void Character::createCharacter(float posX, float posY, float sizeX, float sizeY, bool isPlayer){
	initializeCharacter(posX, posY, sizeX, sizeY, isPlayer);
}
//Asetetaan hahmon kulkusuunta
void Character::setDirection(int dx, int dy){
	this->DX = dx;
	this->DY = dy;
}
//Asetetaan visuaalinen hahmon kulkusuunta.
void Character::setFacingDirection(bool facingLeft){

	if (facingLeft)
		sprite.setScale(1, 1);
	else
		sprite.setScale(-1, 1);

}
//Jos hahmo putoaa, niin siihen pistetään vaikuttamaan painovoima
void Character::applyGravity(float dt){
	if (falling){
		if (this->DY == -1)
			this->velocityY -= 2000 * dt;
		if (this->velocityY <= 0)
			this->setDY(1);
		if (this->DY == 1 && this->velocityY < 500)
			this->velocityY += 2000 * dt;
	}
}
//Asetetaan X suunta
void Character::setDX(int dx){
	this->DX = dx;
}
//Asetetaan Y suunta
void Character::setDY(int dy){
	this->DY = dy;
}
