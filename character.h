#ifndef CHARACTER_H
#define CHARACTER_H
#include "SFML\Graphics.hpp"
#include "Content.h"
using namespace std;
class Character:public sf::RectangleShape {
protected:
	int DX, DY;
	float posX, posY;
	float velocityX, velocityY;
public:
	Character();
	~Character();
	void move();
	void createCharacter(float posX, float posY);
	void setDirection(int DX, int DY);
	void setPosition(float posX, float posY);
	void setDX(int DX);
	void setDY(int DY);
};
#endif;