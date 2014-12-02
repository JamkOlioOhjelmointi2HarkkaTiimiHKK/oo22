#include "Enemy.h"

Enemy::Enemy(){

}
Enemy::Enemy(float posX, float posY, int type){
	create(posX, posY, type);
}
Enemy::Enemy(const Enemy &copy){
	sizeX = copy.sizeX;
	sizeY = copy.sizeY;
	type = copy.type;
	sprite = copy.sprite;
	hitbox = copy.hitbox;
}
void Enemy::update(float dt, float playerposX, float playerposY, Map &ptr, sf::View view){
	switch (type){
	case 0:
		
		this->move(dt);
		hitbox.update(sprite);
		break;
	case 1:
		velocityX = velocityY = 100;
		if (playerposX < sprite.getPosition().x - 25){
			this->setDX(-1);
			this->setFacingDirection(false);
		}
		if (playerposX > sprite.getPosition().x + 25){
			this->setDX(1);
			this->setFacingDirection(true);
		}
		if (playerposY < sprite.getPosition().y - 25){
			this->setDY(-1);
		}
		if (playerposY > sprite.getPosition().y + 25){
			this->setDY(1);
		}
		this->move(dt);
		hitbox.update(sprite);
		//checkCollision(ptr, view);
		break;
	case 2:
		velocityX = 200;

		if (playerposX < sprite.getPosition().x-100){
			this->setDX(-1);
			this->setFacingDirection(false);
		}
		if (playerposX > sprite.getPosition().x + 100){
			this->setDX(1);
			this->setFacingDirection(true);
		}

		if ((playerposX - sprite.getPosition().x)*(playerposX - sprite.getPosition().x) < 22500){
			
			if (this->DY == 0){
				if (this->velocityY <= 0){
					this->setDY(-1);
					
				}
				
			}
			if (!falling){
				if (this->velocityY < 800 && this->DY == -1){
					this->velocityY = 800;
					falling = true;
				}
			}
			else{
				if (this->DY == -1)
					this->velocityY = this->velocityY - 50;
				if (this->velocityY <= 0)
					this->setDY(1);
				if (this->DY == 1 && this->velocityY < 800)
					this->velocityY = this->velocityY + 50;
			}
		}
		this->move(dt);
		hitbox.update(sprite);
		break;
	case 3:
		velocityX = 600;
		if (playerposX < sprite.getPosition().x - 100){
			this->setDX(-1);
			this->setFacingDirection(true);
		}
		if (playerposX > sprite.getPosition().x + 100){
			this->setDX(1);
			this->setFacingDirection(false);
		}
		this->move(dt);
		hitbox.update(sprite);
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
	case 2:
		sizeX = 80;
		sizeY = 40;
		this->createCharacter(posX, posY, sizeX, sizeY, false);
		this->sprite.setTexture(Content::get()->slimeTexture);
		falling = false;
		break;
	case 3:
		sizeX = 100;
		sizeY = 60;
		this->createCharacter(posX, posY, sizeX, sizeY, false);
		this->sprite.setTexture(Content::get()->foxTexture);
		falling = false;
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

	/*
	for (int i = 0; i < ptr.mapObjects.size(); i++){
		if ((ptr.mapObjects[i]->getPos().x - sprite.getPosition().x*(ptr.mapObjects[i]->getPos().x - sprite.getPosition().x)  < 5000 && (ptr.mapObjects[i]->getPos().y - sprite.getPosition().y)*(ptr.mapObjects[i]->getPos().y - sprite.getPosition().y) < 5000)) // tehoja lis��
		{
			if (!ptr.mapObjects[i]->passable){

				if (Utility::boxHit(this->hitbox.enemyBodyHitbox, ptr.mapObjects[i]->shape)){
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
		*/
}
Enemy::~Enemy(){
	
}