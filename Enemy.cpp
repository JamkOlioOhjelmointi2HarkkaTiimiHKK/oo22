#include "Enemy.h"

//Vakio konstruktori
Enemy::Enemy(){

}
//Konstruktori
Enemy::Enemy(float posX, float posY, int type){
	create(posX, posY, type);
}
//Kopio konstruktori
Enemy::Enemy(const Enemy &copy){
	sizeX = copy.sizeX;
	sizeY = copy.sizeY;
	type = copy.type;
	sprite = copy.sprite;
	hitbox = copy.hitbox;
}
//P‰ivitet‰‰n yksitt‰inen vihollinen riippuen mit‰ tyyppi‰ vihollinen edustaa
void Enemy::update(float dt, float playerposX, float playerposY, Map &ptr, sf::View view){
	if (this->isEnemyOnAdjacentSector(ptr, view)){
		switch (type){
		case 0:
			updateJanis(dt, playerposX, playerposY);
			checkCollision(ptr, view);
			break;
		case 1:
			updateGhost(dt, playerposX, playerposY);
			checkCollision(ptr, view);
			break;
		case 2:
			updateSlime(dt, playerposX, playerposY);
			checkCollision(ptr, view);
			break;
		case 3:
			updateFox(dt, playerposX, playerposY);
			checkCollision(ptr, view);
			break;
		default:
			break;
		}
		this->move(dt);
		hitbox.update(sprite);
		checkCollision(ptr, view);
	}
}

void Enemy::updateJanis(float dt, float playerposX, float playerposY){
	applyGravity(dt);
}
void Enemy::updateGhost(float dt, float playerposX, float playerposY){
	velocityX = velocityY = 100;
	if (playerposX < sprite.getPosition().x - 25){
		this->setDX(-1);
		this->setFacingDirection(true);
	}
	if (playerposX > sprite.getPosition().x + 25){
		this->setDX(1);
		this->setFacingDirection(false);
	}
	if (playerposY < sprite.getPosition().y - 25){
		this->setDY(-1);
	}
	if (playerposY > sprite.getPosition().y + 25){
		this->setDY(1);
	}
}
void Enemy::updateSlime(float dt, float playerposX, float playerposY){
	velocityX = 200;

	if (playerposX < sprite.getPosition().x - 100){
		this->setDX(-1);
		this->setFacingDirection(false);
	}
	if (playerposX > sprite.getPosition().x + 100){
		this->setDX(1);
		this->setFacingDirection(true);
	}

	if ((playerposX - sprite.getPosition().x)*(playerposX - sprite.getPosition().x) < 22500){
		jump();
	}
	applyGravity(dt);
}
void Enemy::updateFox(float dt, float playerposX, float playerposY){
	velocityX = 600;
	if (playerposX < sprite.getPosition().x - 100){
		this->setDX(-1);
		this->setFacingDirection(true);
	}
	if (playerposX > sprite.getPosition().x + 100){
		this->setDX(1);
		this->setFacingDirection(false);
	}
	applyGravity(dt);

}
//Kutsutaan, kun vihollinen luodaan (Joko kontruktorissa, tai erikseen kutsuttaessa)
void Enemy::create(float posX, float posY, int type){
	this->type = type;
	switch (type){
	case 0:
		sizeX = 92;
		sizeY = 89;
		this->createCharacter(posX, posY, sizeX, sizeY, false);
		this->sprite.setTexture(Content::get()->janisTexture);
		break;
	case 1:
		sizeX = 40;
		sizeY = 38;
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
//Piirret‰‰n vihollinen
void Enemy::draw(Map &ptr, sf::View view){
	if (isEnemyOnAdjacentSector(ptr, view)){
		window.draw(sprite);
	}
}
//Tutkitaan onko vihollinen pelaajaa viereisell‰ sektorilla
bool Enemy::isEnemyOnAdjacentSector(Map &ptr, sf::View view){
	currentSectorX = floor(view.getCenter().x / 512);
	currentSectorY = floor(view.getCenter().y / 512);

	enemySectorX = floor(sprite.getPosition().x / 512);
	enemySectorY = floor(sprite.getPosition().y / 512);

	for (offsetSectorX = -1; offsetSectorX < 2; ++offsetSectorX)
	{
		for (offsetSectorY = -1; offsetSectorY < 2; ++offsetSectorY)
		{
			adjacentSectorX = currentSectorX + offsetSectorX;
			adjacentSectorY = currentSectorY + offsetSectorY;

			if (adjacentSectorX >= 0 && adjacentSectorY >= 0 && adjacentSectorX < ptr.xRivi.size() && adjacentSectorY < ptr.xRivi.size())
			{
				if (enemySectorX == adjacentSectorX && enemySectorY == adjacentSectorY){
					return true;
				}
			}
		}
	}
	return false;
}
//Vihollisen hypp‰‰miseen k‰ytett‰v‰ funktio
void Enemy::jump(){
	if (!falling){
		if (this->DY == 0){
			if (this->velocityY <= 0){
				this->setDY(-1);
			}
			falling = true;
		}

		if (this->velocityY < 500 && this->DY == -1){
			this->velocityY = 800;

		}
	}
}
//Tarkastetaan tˆrm‰‰kˆ vihollinen
void Enemy::checkCollision(Map &ptr, sf::View view){
	this->legHitboxCollides = false;
	this->bodyLeftHitboxCollides = false;
	this->bodyRightHitboxCollides = false;
	this->headHitboxCollides = false;

	bool legHitboxPriority = false;


	//Saadaan pelaajan nykyinen sektori selville.
	currentSectorX = floor(view.getCenter().x / 512);
	currentSectorY = floor(view.getCenter().y / 512);

//K‰yd‰‰n l‰pi sektorin jokainen maa pala.
				for (int i = 0; i < ptr.xRivi[adjacentSectorX][adjacentSectorY].size(); ++i)
				{
					if (!ptr.xRivi[adjacentSectorX][adjacentSectorY][i]->passable){
						//Jos jalat osuvat maahan
						if (Utility::boxHit(this->hitbox.enemyLegHitbox, ptr.xRivi[adjacentSectorX][adjacentSectorY][i]->shape)){
							if (falling){
								sprite.setPosition(sprite.getPosition().x, ptr.xRivi[adjacentSectorX][adjacentSectorY][i]->getPos().y - this->sizeY / 2 + 1);
								legHitboxPriority = true;
							}
							this->legHitboxCollides = true;
						}
						//Jos p‰‰ osuu kattoon
						else if (Utility::boxHit(this->hitbox.enemyheadHitbox, ptr.xRivi[adjacentSectorX][adjacentSectorY][i]->shape))
						{
							if (this->DY == -1)
							{
								sprite.setPosition(sprite.getPosition().x, ptr.xRivi[adjacentSectorX][adjacentSectorY][i]->getPos().y + ptr.xRivi[adjacentSectorX][adjacentSectorY][i]->getSize().y + this->sizeY / 2 + 1);
								legHitboxPriority = true;
							}
							this->headHitboxCollides = true;
						}
						//Jos kehon vasen puoli osuu sein‰‰n
						if (Utility::boxHit(this->hitbox.enemyBodyleftHitbox, ptr.xRivi[adjacentSectorX][adjacentSectorY][i]->shape)){
							if (!legHitboxPriority)
								sprite.setPosition(ptr.xRivi[adjacentSectorX][adjacentSectorY][i]->getPos().x + ptr.xRivi[adjacentSectorX][adjacentSectorY][i]->getSize().x + this->sizeX / 2 - 1, sprite.getPosition().y);
							this->bodyLeftHitboxCollides = true;
						}
						//Jos kehon oikea puoli osuu sein‰‰n
						else if (Utility::boxHit(this->hitbox.enemyBodyrightHitbox, ptr.xRivi[adjacentSectorX][adjacentSectorY][i]->shape)){
							if (!legHitboxPriority)
								sprite.setPosition(ptr.xRivi[adjacentSectorX][adjacentSectorY][i]->getPos().x - this->sizeX / 2 + 1, sprite.getPosition().y);
							this->bodyRightHitboxCollides = true;
						}
					}
				

			
		
	}
	

	fixValuesBasedOnCollision();
}
void Enemy::fixValuesBasedOnCollision(){

	if (this->legHitboxCollides){
		falling = false;
		this->setDY(0);
		this->velocityY = 0;
		
	}
	else{
		falling = true;
	}
	if (this->headHitboxCollides){
		this->velocityY = 0;
		
	}

	if ((this->DX == -1 && this->bodyLeftHitboxCollides) || (this->DX == 1 && this->bodyRightHitboxCollides)){
		this->setDX(0);
		this->velocityX = 0;
	}

	if (this->legHitboxCollides || this->bodyLeftHitboxCollides || this->bodyRightHitboxCollides){
		hitbox.update(sprite);
	}
	hitbox.update(sprite);
}
//Vihollisen destruktori
Enemy::~Enemy(){
	
}