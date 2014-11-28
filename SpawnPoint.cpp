#include "SpawnPoint.h"


SpawnPoint::SpawnPoint()
{
	name = "spawP";
	shape.setSize(sf::Vector2f(32, 32));
	shape.setFillColor(sf::Color().Blue);
	passable = true;
}

SpawnPoint::SpawnPoint(int x, int y) :MapObject(x, y)
{
	name = "spawP";
	passable = true;
}

SpawnPoint::~SpawnPoint()
{
}
