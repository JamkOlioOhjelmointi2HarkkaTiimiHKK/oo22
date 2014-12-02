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
		checkCollision(ptr, view);
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

void Enemy::draw(Map &ptr, sf::View view){
	int xxx = floor(view.getCenter().x / 512);
	int yyy = floor(view.getCenter().y / 512);

	for (int xx = -1; xx < 2; ++xx)
	{
		for (int yy = -1; yy < 2; ++yy)
		{
			if (xxx + xx >= 0 && yyy + yy >= 0 && xxx + xx < ptr.xRivi.size() && yyy + yy < ptr.xRivi.size())
			{
				for (int i = 0; i < ptr.xRivi[xxx + xx][yyy + yy].size(); ++i)
				{
					window.draw(sprite);					
				}

			}
		}
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

	int xxx = floor(view.getCenter().x / 512);
	int yyy = floor(view.getCenter().y / 512);

	for (int xx = -1; xx < 2; ++xx)
	{
		for (int yy = -1; yy < 2; ++yy)
		{
			if (xxx + xx >= 0 && yyy + yy >= 0 && xxx + xx < ptr.xRivi.size() && yyy + yy < ptr.xRivi.size())
			{
				for (int i = 0; i < ptr.xRivi[xxx + xx][yyy + yy].size(); ++i)
				{
					if (!ptr.xRivi[xxx + xx][yyy + yy][i]->passable){

						if (Utility::boxHit(this->hitbox.enemyBodyHitbox, ptr.xRivi[xxx + xx][yyy + yy][i]->shape)){
								sprite.setPosition(sprite.getPosition().x, ptr.xRivi[xxx + xx][yyy + yy][i]->getPos().y - this->sizeY / 2 + 1);
								sprite.setPosition(ptr.xRivi[xxx + xx][yyy + yy][i]->getPos().x + ptr.xRivi[xxx + xx][yyy + yy][i]->getSize().x + this->sizeX / 2 - 1, sprite.getPosition().y);
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
			}
		}
	
	
		hitbox.update(sprite);
		
}
Enemy::~Enemy(){
	
}