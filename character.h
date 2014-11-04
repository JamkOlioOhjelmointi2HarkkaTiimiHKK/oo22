#ifndef CHARACTER_H
#define CHARACTER_H
#include "SFML\Graphics.hpp"
#include "Content.h"
using namespace std;
class Character:public sf::RectangleShape {
protected:
	int DX, DY;
	float velocityX, velocityY;
public:
	Character();
	~Character();
	void move(float dt);
	void draw(sf::RenderWindow &window);
	void createCharacter(float posX, float posY);
	void setDirection(int DX, int DY);
	void setDX(int DX);
	void setDY(int DY);
};
#endif;