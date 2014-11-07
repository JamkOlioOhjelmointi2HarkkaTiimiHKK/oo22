#include "Block.h"


Block::Block()
{
	name = "block";
	shape.setSize(sf::Vector2f(32, 32));
	shape.setFillColor(sf::Color().Green);
	passable = false;
}


Block::~Block()
{
	delete this;
}
