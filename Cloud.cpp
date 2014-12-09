#include "Cloud.h"


Cloud::Cloud()
{
	shape.setSize(sf::Vector2f(Utility::random(70,120), Utility::random(70,120)));
	passable = true;
	shape.setTexture(&Content::get()->cloudTexture);
	speed =  (float) (rand()) / (float) (RAND_MAX / 1);
}



Cloud::~Cloud()
{
}
