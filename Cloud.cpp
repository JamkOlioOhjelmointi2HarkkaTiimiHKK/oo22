#include "Cloud.h"


Cloud::Cloud()
{
	srand(static_cast <unsigned> (time(0)));
	shape.setSize(sf::Vector2f(Utility::random(20,40), Utility::random(20,40)));
	passable = true;
	shape.setTexture(&Content::get()->cloudTexture);
	speed = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / 1));
}


Cloud::~Cloud()
{
}
