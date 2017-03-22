#include "SpawnEnemy.h"


SpawnEnemy::SpawnEnemy()
{
	name = "spawE";
	shape.setSize(sf::Vector2f(32, 32));
	shape.setFillColor(sf::Color().Red);
	passable = true;
}

SpawnEnemy::SpawnEnemy(int x, int y) :MapObject(x, y)
{
	name = "spawE";
	passable = true;
}

SpawnEnemy::~SpawnEnemy()
{
}
