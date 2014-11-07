#include "Floor.h"


Floor::Floor()
{
	name = "floor";
	shape.setSize(sf::Vector2f(32*5, 32));
	shape.setFillColor(sf::Color().Green);
	passable = false;
}


Floor::~Floor()
{
	delete this;
}
