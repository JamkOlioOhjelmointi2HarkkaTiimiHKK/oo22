#include "Enemy.h"

Enemy::Enemy(){

}

void Enemy::update(float dt, float playerposX, float playerposY, Map &ptr, sf::View view){
	switch (type){
	case 0:
		
		this->move(dt);
		hitbox.update(sprite);
		break;
	case 1:
		velocityX = velocityY = 100;
		if (playerposX < sprite.getPosition().x){
			this->setDX(-1);
		}
		else{
			this->setDX(1);
		}
		if (playerposY < sprite.getPosition().y){
			this->setDY(-1);
		}
		else{
			this->setDY(1);
		}
		this->move(dt);
		hitbox.update(sprite);
		checkCollision(ptr, view);
		break;
	default:
		break;
	}
	
}

void Enemy::create(float posX, float posY, int type){
	this->type = type;
	switch (type){
	case 0:
		sizeX = 32;
		sizeY = 64;
		this->createCharacter(posX, posY, sizeX, sizeY, false);
		this->sprite.setTexture(Content::get()->janisTexture);
		break;
	case 1:
		sizeX = 40;
		sizeY = 40;
		this->createCharacter(posX, posY, sizeX, sizeY, false);
		this->sprite.setTexture(Content::get()->ghostTexture);
		break;
	default:
		break;
	}
	
}
void Enemy::applyGravity(){
	if (falling){
		if (this->DY == -1)
			this->velocityY = this->velocityY - 50;
		if (this->velocityY <= 0)
			this->setDY(1);
		if (this->DY == 1 && this->velocityY < 500)
			this->velocityY = this->velocityY + 50;
	}
}
void Enemy::jump(){
	
	if (this->DY == 0){
		if (this->velocityY <= 0){
			this->setDY(-1);
		}
		falling = true;
	}
	if (!falling){
		if (this->velocityY < 500 && this->DY == -1){
			this->velocityY = 500;
		}
	}
	
}
void Enemy::checkCollision(Map &ptr, sf::View view){


	for (int i = 0; i < ptr.mapObjects.size(); i++){
		if ((ptr.mapObjects[i]->getPos().x - sprite.getPosition().x*(ptr.mapObjects[i]->getPos().x - sprite.getPosition().x)  < 3000 && (ptr.mapObjects[i]->getPos().y - sprite.getPosition().y)*(ptr.mapObjects[i]->getPos().y - sprite.getPosition().y) < 3000)) // tehoja lisää
		{
			if (!ptr.mapObjects[i]->passable){

				if (Utility::boxHit(this->hitbox.fullHitbox, ptr.mapObjects[i]->shape)){
						sprite.setPosition(sprite.getPosition().x, ptr.mapObjects[i]->getPos().y - this->sizeY / 2 + 1);
						sprite.setPosition(ptr.mapObjects[i]->getPos().x + ptr.mapObjects[i]->getSize().x + this->sizeX / 2 - 1, sprite.getPosition().y);
						this->setDY(0);
						this->velocityY = 0;
						this->setDX(0);
						this->velocityX = 0;
				}

				//else if (Utility::boxHit(this->hitbox.bodyRightHitbox, ptr.mapObjects[i]->shape)){
					//	sprite.setPosition(ptr.mapObjects[i]->getPos().x - this->sizeX / 2 + 1, sprite.getPosition().y);
					//this->bodyRightHitbocCollides = true;
				//}
			}
		}
	}

	
		
	
	
		hitbox.update(sprite);

}
Enemy::~Enemy(){
	
}