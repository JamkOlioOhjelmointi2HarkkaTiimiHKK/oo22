#ifndef HITBOX_H
#define HITBOX_H
#include "globals.h"
#include "SFML\Graphics.hpp"
class Hitbox{

private:
	bool isPlayer;
public:
	Hitbox();
	~Hitbox();
	sf::RectangleShape legHitbox;
	sf::RectangleShape bodyHitbox;
	sf::RectangleShape bodyLeftHitbox;
	sf::RectangleShape bodyRightHitbox;
	sf::RectangleShape headHitbox;
	sf::RectangleShape fullHitbox;
	void initializeHitBoxes(sf::Sprite sprite, float sizeX, float sizeY, bool isPlayer);
	void update(sf::Sprite sprite);
	void draw();

};
#endif;