#include "Block.h"


Block::Block()
{
	name = "block";
	shape.setSize(sf::Vector2f(32, 32));
	passable = false;
	shape.setTexture(&Content::get()->blockTexture);
}

Block::Block(int x, int y):MapObject(x, y)
{
	name = "block";
	shape.setSize(sf::Vector2f(32, 32));
	passable = false;
	shape.setTexture(&Content::get()->blockTexture);
}

Block::~Block()
{
	delete this;
}
