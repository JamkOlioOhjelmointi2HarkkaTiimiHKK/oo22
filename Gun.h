#ifndef GUN_H
#define GUN_H
#include "globals.h"
#include "Content.h"
#include "SFML\Graphics.hpp"

class Gun:public sf::RectangleShape{
private:
	int sizeX, sizeY;
public:
	Gun();
	~Gun();
	sf::Sprite handSprite;
	void create();
	void update(sf::Sprite sprite);
	void draw();
};
#endif;