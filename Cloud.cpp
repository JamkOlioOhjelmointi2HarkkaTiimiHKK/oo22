#include "Cloud.h"


Cloud::Cloud()
{
	size = Utility::random(50, 120);
	shape.setSize(sf::Vector2f(size, size));
	passable = true;
	shape.setTexture(&Content::get()->cloudTexture);
	if (size > 100)
		speed = (float)(rand()) / (float)(RAND_MAX)/2.0 + 0.5; // 0.5 - 1
	else
		speed = (float)(rand()) / (float)(RAND_MAX)/2.0; // 0 - 0.5
}



Cloud::~Cloud()
{
}
