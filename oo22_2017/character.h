#ifndef CHARACTER_H
#define CHARACTER_H
#include "SFML\Graphics.hpp"
#include "Content.h"
#include "Hitbox.h"
using namespace std;
class Character:public sf::RectangleShape {
protected:
	int DX, DY;
	float velocityX, velocityY;
	float sizeX, sizeY;
	sf::Sprite sprite;
	bool falling;
	bool recentlyjumped;
	Hitbox hitbox;
	bool legHitboxCollides, bodyHitboxCollides, bodyLeftHitboxCollides, bodyRightHitboxCollides, headHitboxCollides, enemyCollides;
	int currentSectorX, currentSectorY;
	int offsetSectorX, offsetSectorY;
	int adjacentSectorX, adjacentSectorY;
	bool isFacingLeft;
public:
	Character();
	~Character();
	void initializeCharacter(float posX, float posY, float sizeX, float sizeY, bool isPlayer);
	void move(float dt);
	void draw();
	void drawHitboxes();
	void createCharacter(float posX, float posY, float sizeX, float sizeY, bool isPlayer);
	void createCharacter(sf::Vector2f position, sf::Vector2f size, bool isPlayer);
	void setDirection(int DX, int DY);
	void setFacingDirection(bool facingLeft);
	void applyGravity(float dt);
	void setDX(int DX);
	void setDY(int DY);
	float getCharacterMovementX(float dt);
};
#endif;