#include "player.h"

Player::Player(){
	
}

void Player::create(float posX, float posY, float sizeX, float sizeY){
	this->createCharacter(posX, posY, sizeX, sizeY, true);
	this->sprite.setTexture(Content::get()->playerTexture);
	this->gun.create(sprite);
}
//Päivitetään pelaaja
void Player::update(float dt, Map &ptr,sf::View view){
	
	updateMovement(dt);
	if (!isClimbing){
		applyGravity(dt);
	}
	this->move(dt);
	hitbox.update(sprite);
	checkCollision(ptr, view);
	updateGun();
}
//Kuunnellaan mitä näppäimiä pelaaja painaa
void Player::updateMovement(float dt){

	if ((Controls::get()->iskeydown(sf::Keyboard::A)) && (Controls::get()->iskeydown(sf::Keyboard::D))){
		deceleratePlayerX(dt);
	}

	else if (Controls::get()->iskeydown(sf::Keyboard::A)){
		if (DX <= 0){
			this->setDX(-1);
			acceleratePlayerX(dt);
			this->setFacingDirection(false);
		}
		else{
			deceleratePlayerX(dt);
		}
	}

	else if (Controls::get()->iskeydown(sf::Keyboard::D)){
		if (DX >= 0){
			this->setDX(1);
			acceleratePlayerX(dt);
			this->setFacingDirection(true);
		}
		else{
			deceleratePlayerX(dt);
		}
	}

	else{
		deceleratePlayerX(dt);
	}

	if (canClimb){
		if (Controls::get()->iskeydown(sf::Keyboard::W) && canClimbUp){
			falling = false;
			isClimbing = true;
			this->setDY(-1);
			velocityY = 40000 * dt;
		}
		else if (Controls::get()->iskeydown(sf::Keyboard::S) && canClimbDown){
			falling = false;
			isClimbing = true;
			this->setDY(1);
			velocityY = 40000 * dt;
		}
		else{
			velocityY = 0;
		}
	}
	else{
		isClimbing = false;
		
	}

	if (Controls::get()->iskeydown(sf::Keyboard::Space)){
		isClimbing = false;
		jump(dt);
	}
}
void Player::acceleratePlayerX(float dt){
	if (this->velocityX < 500)
		this->velocityX += 2000 * dt;
}
void Player::deceleratePlayerX(float dt){
	if (velocityX <= 0)
		this->setDX(0);
	else
		velocityX -= 2000 * dt;
}
//Pelaajan hyppy logiikka
void Player::jump(float dt){
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
void Player::playerHit(){
	velocityX = 500;
	velocityY = 500;
	setDX(-1);
	setDY(-1);
	falling = true;
	recentlyjumped = true;
}
//Tarkistetaan osuuko pelaaja maastoon
void Player::checkCollision(Map &ptr, sf::View view){

	this->legHitboxCollides = false;
	this->bodyLeftHitboxCollides = false;
	this->bodyRightHitboxCollides = false;
	this->headHitboxCollides = false;

	bool legHitboxPriority = false;

	doesTouchLadder = false;
	
	//Saadaan pelaajan nykyinen sektori selville.
	currentSectorX = floor(view.getCenter().x / 512);
	currentSectorY = floor(view.getCenter().y / 512);
	
	for (offsetSectorX = -1; offsetSectorX < 2; ++offsetSectorX)
	{
		for (offsetSectorY = -1; offsetSectorY < 2; ++offsetSectorY)
		{
			//Viereinen sektori pelaajasta katsottuna. (Mukaanlukien viistoon ja pelaajan oma sektori)
			adjacentSectorX = currentSectorX + offsetSectorX;
			adjacentSectorY = currentSectorY + offsetSectorY;

			//Tarkastetaan, ettei viereiset sektorit ylitä rajoja
			if (adjacentSectorX >= 0 && adjacentSectorY >= 0 && adjacentSectorX < ptr.xRivi.size() && adjacentSectorY < ptr.xRivi.size())
			{
				//Käydään läpi sektorin jokainen maa pala.
				for (int i = 0; i < ptr.xRivi[adjacentSectorX][adjacentSectorY].size(); ++i)
				{
					//Jos palan läpi ei voi mennä
					if (!ptr.xRivi[adjacentSectorX][adjacentSectorY][i]->passable){
						//Jos jalat osuvat maahan
						if (Utility::boxHit(this->hitbox.legHitbox, ptr.xRivi[adjacentSectorX][adjacentSectorY][i]->shape)){
							if (falling){
								sprite.setPosition(sprite.getPosition().x, ptr.xRivi[adjacentSectorX][adjacentSectorY][i]->getPos().y - this->sizeY / 2 + 1);
								legHitboxPriority = true;
							}
							this->legHitboxCollides = true;
						}
						//Jos pää osuu kattoon
						else if (Utility::boxHit(this->hitbox.headHitbox, ptr.xRivi[adjacentSectorX][adjacentSectorY][i]->shape))
						{
							if (this->DY == -1)
							{
								sprite.setPosition(sprite.getPosition().x, ptr.xRivi[adjacentSectorX][adjacentSectorY][i]->getPos().y + ptr.xRivi[adjacentSectorX][adjacentSectorY][i]->getSize().y + this->sizeY / 2 + 1);
								legHitboxPriority = true;
							}
							this->headHitboxCollides = true;
						}
						//Jos kehon vasen puoli osuu seinään
						if (Utility::boxHit(this->hitbox.bodyLeftHitbox, ptr.xRivi[adjacentSectorX][adjacentSectorY][i]->shape)){
							if (!legHitboxPriority)
								sprite.setPosition(ptr.xRivi[adjacentSectorX][adjacentSectorY][i]->getPos().x + ptr.xRivi[adjacentSectorX][adjacentSectorY][i]->getSize().x + this->sizeX / 2 - 1, sprite.getPosition().y);
							this->bodyLeftHitboxCollides = true;
						}
						//Jos kehon oikea puoli osuu seinään
						else if (Utility::boxHit(this->hitbox.bodyRightHitbox, ptr.xRivi[adjacentSectorX][adjacentSectorY][i]->shape)){
							if (!legHitboxPriority)
								sprite.setPosition(ptr.xRivi[adjacentSectorX][adjacentSectorY][i]->getPos().x - this->sizeX / 2 + 1, sprite.getPosition().y);
							this->bodyRightHitboxCollides = true;
						}
					}
					//Jos kyseessä on esim. tikkaat
					else{
						if (Utility::boxHit(this->hitbox.bodyHitbox, ptr.xRivi[adjacentSectorX][adjacentSectorY][i]->shape)){
							doesTouchLadder = true;
						}
						
						
					}
				}

			}
		}
	}

	fixValuesBasedOnCollision();
}
//Korjataan pelaajan arvoja törmäyksistä riippuen
void Player::fixValuesBasedOnCollision(){

	canClimb = canClimbUp = canClimbDown = false;
	

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

	if (doesTouchLadder){
		canClimb = true;
		if (this->legHitboxCollides){
			canClimbUp = true;
			canClimbDown = false;
		}
		else if (this->headHitboxCollides){
			canClimbUp = false;
			canClimbDown = true;
		}
		else{
			canClimbUp = true;
			canClimbDown = true;
		}
	}

	if (this->legHitboxCollides || this->bodyLeftHitboxCollides || this->bodyRightHitboxCollides ||this->headHitboxCollides){
		hitbox.update(sprite);
	}
}
void Player::updateGun(){
	gun.update(this->sprite, isFacingLeft);
}
void Player::drawGun(){
	gun.draw();
}
sf::RectangleShape Player::getbody(){
	return this->hitbox.bodyHitbox;
}
//Palautetaan pelaajan sprite
sf::Sprite Player::getSprite()
{
	return sprite;
}

Player::~Player(){

}