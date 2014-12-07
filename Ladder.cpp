#include "Ladder.h"


Ladder::Ladder()
{
	name = "ladde";
	shape.setSize(sf::Vector2f(32, 32*5));
	//shape.setFillColor(sf::Color().Yellow);
	passable = true;
	shape.setTexture(&Content::get()->ladderTexture);
}

Ladder::Ladder(int x, int y) : MapObject(x, y)
{
	name = "ladde";
	shape.setSize(sf::Vector2f(32, 32*5));
	//shape.setFillColor(sf::Color().Yellow);
	passable = true;
	shape.setTexture(&Content::get()->ladderTexture);
}

Ladder::~Ladder()
{
}
