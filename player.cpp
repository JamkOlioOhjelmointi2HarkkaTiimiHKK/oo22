#include "player.h"

Player::Player(){
	
}

void Player::create(float posX, float posY, float sizeX, float sizeY){
	this->createCharacter(posX, posY, sizeX, sizeY, true);
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
			this->velocityY -= 50;
		if (this->velocityY <= 0)
			this->setDY(1);
		if (this->DY == 1 && this->velocityY < 500)
			this->velocityY += 50;
	}
}
/*
void Player::checkCollision(Map &ptr, sf::View view){

	this->legHitboxCollides = false;
	this->bodyLeftHitboxCollides = false;
	this->bodyRightHitboxCollides = false;
	this->headHitboxCollides = false;

	bool legHitboxPriority = false;
	
	int xxx = ceil(view.getCenter().x / 512);
	int yyy = ceil(view.getCenter().y / 512);

	for (int xx = -1; xx < 2; ++xx)
	{
		for (int yy = -1; yy < 2; ++yy)
		{
			if (xxx + xx >= 0 && yyy + yy >= 0 && xxx + xx < ptr.xRivi.size() && yyy + yy < ptr.xRivi.size())
			{
				for (int i = 0; i < ptr.xRivi[xxx + xx][yyy + yy].size(); ++i)
				{
					for (int i = 0; i < ptr.xRivi[xxx + xx][yyy + yy].size(); ++i)
					{
						if (!ptr.xRivi[xxx + xx][yyy + yy][i]->passable)
						{

							if (Utility::boxHit(this->hitbox.legHitbox, ptr.xRivi[xxx][yyy][i]->shape))
							{
								if (falling)
								{
									sprite.setPosition(sprite.getPosition().x, ptr.xRivi[xxx][yyy][i]->getPos().y - this->sizeY / 2 + 1);
									legHitboxPriority = true;
								}
								this->legHitboxCollides = true;
							}
							else if (Utility::boxHit(this->hitbox.headHitbox, ptr.xRivi[xxx][yyy][i]->shape))
							{
								if (this->DY == -1)
								{
									sprite.setPosition(sprite.getPosition().x, ptr.xRivi[xxx][yyy][i]->getPos().y + ptr.xRivi[xxx][yyy][i]->getSize().y + this->sizeY / 2 + 1);
									legHitboxPriority = true;
								}
								this->headHitboxCollides = true;
							}

							if (Utility::boxHit(this->hitbox.bodyLeftHitbox, ptr.xRivi[xxx][yyy][i]->shape))
							{
								if (!legHitboxPriority)
									sprite.setPosition(ptr.xRivi[xxx][yyy][i]->getPos().x + ptr.xRivi[xxx][yyy][i]->getSize().x + this->sizeX / 2 - 1, sprite.getPosition().y);
								this->bodyLeftHitboxCollides = true;
							}

							else if (Utility::boxHit(this->hitbox.bodyRightHitbox, ptr.xRivi[xxx][yyy][i]->shape))
							{
								if (!legHitboxPriority)
									sprite.setPosition(ptr.xRivi[xxx][yyy][i]->getPos().x - this->sizeX / 2 + 1, sprite.getPosition().y);
								this->bodyRightHitboxCollides = true;
							}
						}
					}
				}
			if (this->legHitboxCollides){
				falling = false;
				this->setDY(0);
				this->velocityY = 0;
				recentlyjumped = false;
			}
			else{
				falling = true;
			}

			if (this->headHitboxCollides){
				this->velocityY = 0;
				recentlyjumped = true;
			}

			if ((this->DX == -1 && this->bodyLeftHitboxCollides) || (this->DX == 1 && this->bodyRightHitboxCollides)){
				this->setDX(0);
				this->velocityX = 0;
			}

			if (this->legHitboxCollides || this->bodyLeftHitboxCollides || this->bodyRightHitboxCollides || this->headHitboxCollides){
				hitbox.update(sprite);
			}
					}
				}

	}
}
*/

void Player::checkCollision(Map &ptr, sf::View view){

	this->legHitboxCollides = false;
	this->bodyLeftHitboxCollides = false;
	this->bodyRightHitboxCollides = false;

	bool legHitboxPriority = false;

	int xxx = ceil(view.getCenter().x / 512);
	int yyy = ceil(view.getCenter().y / 512);

	for (int xx = -1; xx < 2; ++xx)
	{
		for (int yy = -1; yy < 2; ++yy)
		{
			if (xxx + xx >= 0 && yyy + yy >= 0 && xxx + xx < ptr.xRivi.size() && yyy + yy < ptr.xRivi.size())
			{
				for (int i = 0; i < ptr.xRivi[xxx + xx][yyy + yy].size(); ++i)
				{
					if (!ptr.xRivi[xxx + xx][yyy + yy][i]->passable){

						if (Utility::boxHit(this->hitbox.legHitbox, ptr.xRivi[xxx + xx][yyy + yy][i]->shape)){
							if (falling){
								sprite.setPosition(sprite.getPosition().x, ptr.xRivi[xxx + xx][yyy + yy][i]->getPos().y - this->sizeY / 2 + 1);
								legHitboxPriority = true;
							}
							this->legHitboxCollides = true;
						}

						if (Utility::boxHit(this->hitbox.bodyLeftHitbox, ptr.xRivi[xxx + xx][yyy + yy][i]->shape)){
							if (!legHitboxPriority)
								sprite.setPosition(ptr.xRivi[xxx + xx][yyy + yy][i]->getPos().x + ptr.xRivi[xxx + xx][yyy + yy][i]->getSize().x + this->sizeX / 2 - 1, sprite.getPosition().y);
							this->bodyLeftHitboxCollides = true;
						}

						else if (Utility::boxHit(this->hitbox.bodyRightHitbox, ptr.xRivi[xxx + xx][yyy + yy][i]->shape)){
							if (!legHitboxPriority)
								sprite.setPosition(ptr.xRivi[xxx + xx][yyy + yy][i]->getPos().x - this->sizeX / 2 + 1, sprite.getPosition().y);
							this->bodyRightHitboxCollides = true;
						}
					}
				}

			}
		}

		if (this->legHitboxCollides){
			falling = false;
			this->setDY(0);
			this->velocityY = 0;
			recentlyjumped = false;
		}
		else{
			falling = true;
		}

		if ((this->DX == -1 && this->bodyLeftHitboxCollides) || (this->DX == 1 && this->bodyRightHitboxCollides)){
			this->setDX(0);
			this->velocityX = 0;
		}

		if (this->legHitboxCollides || this->bodyLeftHitboxCollides || this->bodyRightHitboxCollides){
			hitbox.update(sprite);
		}

	}

}


sf::Sprite Player::getSprite()
{
	return sprite;
}

Player::~Player(){

}