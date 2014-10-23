#ifndef CHARACTER_H
#define CHARACTER_H
#include "SFML\Graphics.hpp"
using namespace std;
class Character:public sf::RectangleShape {
protected:
	int DX, DY;
	int posX, posY;
	float velocityX, velocityY;
public:
	Character();
	~Character();
	void move();
	void setDirection(int DX, int DY);
	void setPosition(int posX, int posY);
	void setDX(int DX);
	void setDY(int DY);
};
#endif;