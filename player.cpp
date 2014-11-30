#include "player.h"

Player::Player(){
	
}

void Player::create(float posX, float posY, float sizeX, float sizeY){
	this->createCharacter(posX, posY, sizeX, sizeY);
	this->sprite.setTexture(Content::get()->playerTexture);
	this->gun.create();
}
void Player::update(float dt, Map &ptr,sf::View view){
	
	updateMovement();
	applyGravity();
	this->move(dt);
	hitbox.update(sprite);
	checkCollision(ptr, view);
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

void Player::checkCollision(Map &ptr, sf::View view){

	this->legHitbocCollides = false;
	this->bodyLeftHitbocCollides = false;
	this->bodyRightHitbocCollides = false;

	bool legHitboxPriority = false;

	for (int i = 0; i < ptr.mapObjects.size(); i++){
		if ((ptr.mapObjects[i]->getPos().x - view.getCenter().x)*(ptr.mapObjects[i]->getPos().x - view.getCenter().x)  < halfScreenX*halfScreenX && (ptr.mapObjects[i]->getPos().y - view.getCenter().y)*(ptr.mapObjects[i]->getPos().y - view.getCenter().y) < halfscreenY*halfscreenY) // tehoja lisää
		{
			if (!ptr.mapObjects[i]->passable){

				if (Utility::boxHit(this->hitbox.legHitbox, ptr.mapObjects[i]->shape)){
					if (falling){
						sprite.setPosition(sprite.getPosition().x, ptr.mapObjects[i]->getPos().y - this->sizeY / 2 + 1);
						legHitboxPriority = true;
					}
					this->legHitbocCollides = true;
				}

				if (Utility::boxHit(this->hitbox.bodyLeftHitbox, ptr.mapObjects[i]->shape)){
					if (!legHitboxPriority)
						sprite.setPosition(ptr.mapObjects[i]->getPos().x + ptr.mapObjects[i]->getSize().x + this->sizeX / 2 - 1, sprite.getPosition().y);
					this->bodyLeftHitbocCollides = true;
				}

				else if (Utility::boxHit(this->hitbox.bodyRightHitbox, ptr.mapObjects[i]->shape)){
					if (!legHitboxPriority)
						sprite.setPosition(ptr.mapObjects[i]->getPos().x - this->sizeX / 2 + 1, sprite.getPosition().y);
					this->bodyRightHitbocCollides = true;
				}
			}
		}
	}

	if (this->legHitbocCollides){
		falling = false;
		this->setDY(0);
		this->velocityY = 0;
		recentlyjumped = false;
	}
	else{
		falling = true;
	}

	if ((this->DX == -1 && this->bodyLeftHitbocCollides) || (this->DX == 1 && this->bodyRightHitbocCollides)){
		this->setDX(0);
		this->velocityX = 0;
	}

	if (this->legHitbocCollides || this->bodyLeftHitbocCollides || this->bodyRightHitbocCollides){
		hitbox.update(sprite);
	}

}

sf::Sprite Player::getSprite()
{
	return sprite;
}

Player::~Player(){

}