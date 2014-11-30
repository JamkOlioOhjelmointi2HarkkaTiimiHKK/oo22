#include "player.h"

Player::Player(){
	
}

void Player::create(float posX, float posY, float sizeX, float sizeY){
	this->createCharacter(posX, posY, sizeX, sizeY);
	this->sprite.setTexture(Content::get()->playerTexture);
}
void Player::update(float dt, Map &ptr,sf::View view){
	
	checkLegCollision(ptr,view);
	updateMovement();
	
	checkBodyCollision(ptr, view);
	applyGravity();
	this->move(dt);
	hitbox.update(sprite);


}
void Player::updateMovement(){

	if ((Controls::get()->iskeydown(sf::Keyboard::A)) && (Controls::get()->iskeydown(sf::Keyboard::D))){
		deceleratePlayerX();
	}

	else if (Controls::get()->iskeydown(sf::Keyboard::A)){
		if (DX <= 0){
			this->setDX(-1);
			acceleratePlayerX();
			this->setFacingDirection(false);
		}
		else{
			deceleratePlayerX();
		}
	}

	else if (Controls::get()->iskeydown(sf::Keyboard::D)){
		if (DX >= 0){
			this->setDX(1);
			acceleratePlayerX();
			this->setFacingDirection(true);
		}
		else{
			deceleratePlayerX();
		}
	}

	else{
		deceleratePlayerX();
	}

	if (Controls::get()->iskeydown(sf::Keyboard::Space)){
		jump();
	}
}
void Player::acceleratePlayerX(){
	if (this->velocityX < 500)
		this->velocityX += 50;
}
void Player::deceleratePlayerX(){
	if (velocityX <= 0)
		this->setDX(0);
	else
		velocityX -= 50;
}

void Player::jump(){
	if (!falling){
		jumpstart = sprite.getPosition().y;
	}

	if (this->DY == 0){
		if (this->velocityY <= 0){
			this->setDY(-1);
		}
		falling = true;
	}
	if (!recentlyjumped){
		if (this->velocityY < 500 && this->DY == -1){
			this->velocityY = 500;
		}
	}
	if ((jumpstart - sprite.getPosition().y > 100)){
		recentlyjumped = true;
	}
}

void Player::applyGravity(){
	if (falling){
		if (this->DY == -1)
			this->velocityY = this->velocityY - 50;
		if (this->velocityY <= 0)
			this->setDY(1);
		if (this->DY == 1 && this->velocityY < 500)
			this->velocityY = this->velocityY + 50;
	}
}

void Player::checkLegCollision(Map &ptr,sf::View view){


	for (int i = 0; i < ptr.mapObjects.size(); i++){
		if (std::pow(ptr.mapObjects[i]->getPos().x - view.getCenter().x, 2) - 350 < std::pow(halfScreenX, 2) && std::pow(ptr.mapObjects[i]->getPos().y - view.getCenter().y, 2) - 350 < std::pow(halfscreenY, 2))
		if (Utility::boxHit(this->hitbox.legHitbox, ptr.mapObjects[i]->shape)){
			falling = false;
			this->setDY(0);
			this->velocityY = 0;
			recentlyjumped = false;
			sprite.setPosition(sprite.getPosition().x, ptr.mapObjects[i]->getPos().y - this->sizeY / 2 + 1);
			this->legHitbocCollides = true;
		}
	}
	if (!this->legHitbocCollides){
		falling = true;
	}

	this->legHitbocCollides = false;

}
void Player::checkBodyCollision(Map &ptr,sf::View view){
	for (int i = 0; i < ptr.mapObjects.size(); i++){
		if (std::pow(ptr.mapObjects[i]->getPos().x - view.getCenter().x, 2) - 350 < std::pow(halfScreenX, 2) && std::pow(ptr.mapObjects[i]->getPos().y - view.getCenter().y, 2) - 350 < std::pow(halfscreenY, 2))
		{

			if (Utility::boxHit(this->hitbox.bodyLeftHitbox, ptr.mapObjects[i]->shape)){
				sprite.setPosition(ptr.mapObjects[i]->getPos().x + ptr.mapObjects[i]->getSize().x + this->sizeX / 2 - 1, sprite.getPosition().y);
				this->bodyLeftHitbocCollides = true;
			}

			if (Utility::boxHit(this->hitbox.bodyRightHitbox, ptr.mapObjects[i]->shape)){
				sprite.setPosition(ptr.mapObjects[i]->getPos().x - this->sizeX / 2 + 1, sprite.getPosition().y);
				this->bodyRightHitbocCollides = true;
			}
		}
	}

	if ((this->DX == -1 && this->bodyLeftHitbocCollides) || (this->DX == 1 && this->bodyRightHitbocCollides)){
		this->setDX(0);
		this->velocityX = 0;
	}


	this->bodyLeftHitbocCollides = false;
	this->bodyRightHitbocCollides = false;
}

sf::Sprite Player::getSprite()
{
	return sprite;
}

Player::~Player(){

}