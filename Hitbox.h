#ifndef HITBOX_H
#define HITBOX_H
#include "globals.h"
#include "SFML\Graphics.hpp"
class Hitbox{

public:
	Hitbox();
	~Hitbox();
	sf::RectangleShape legHitbox;
	sf::RectangleShape bodyHitbox;
	sf::RectangleShape headHitbox;
	void initializeHitBoxes(sf::Sprite sprite, float sizeX, float sizeY);
	void update(sf::Sprite sprite);
	void draw(sf::RenderWindow &window);

};


#endif;