#ifndef GUN_H
#define GUN_H
#include "globals.h"
#include "Content.h"
#include "SFML\Graphics.hpp"
#include "Controls.h"

class Gun:public sf::RectangleShape{
private:
	int sizeX, sizeY;
	sf::Vector2f mousePos;
public:
	Gun();
	~Gun();
	sf::Sprite handSprite;
	void create(sf::Sprite sprite);
	void update(sf::Sprite sprite, bool isFacinating);
	void updateCursor();
	void draw();
};
#endif;