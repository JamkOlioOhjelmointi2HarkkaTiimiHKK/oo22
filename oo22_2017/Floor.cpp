#include "Floor.h"


Floor::Floor()
{
	name = "floor";
	shape.setSize(sf::Vector2f(32*5, 32));
	//shape.setFillColor(sf::Color().Green);
	passable = false;
	shape.setTexture(&Content::get()->floorTexture);
}

Floor::Floor(int x, int y) :MapObject(x,y)
{
	name = "floor";
	shape.setSize(sf::Vector2f(32 * 5, 32));
	//shape.setFillColor(sf::Color().Green);
	passable = false;
	shape.setTexture(&Content::get()->floorTexture);
}

Floor::~Floor()
{
	delete this;
}
