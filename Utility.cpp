#include "Utility.h"
#include <math.h>

sf::Vector2f Utility::makeDirVector(sf::Vector2f &vec)
{
	return vec / std::sqrtf(std::pow(vec.x, 2) + std::pow(vec.y, 2));
}

sf::Vector2f Utility::makeDirVector(sf::Vector2f &from, sf::Vector2f &to)
{
	sf::Vector2f dif = to - from;
	return dif / std::sqrtf(std::pow(dif.x, 2) + std::pow(dif.y, 2));
}

bool Utility::boxHit(const sf::IntRect &box1, const sf::IntRect &box2)
{
	return box1.intersects(box2); 
}

bool Utility::circleHit(const float rad1, const float rad2, const float dist)
{
	return rad1 + rad2 >= dist;
}

float Utility::distance(const sf::Vector2f &pos1, const sf::Vector2f &pos2)
{
	sf::Vector2f difference = pos2 - pos1;
	return std::sqrt(std::powf(difference.x, 2) + std::powf(difference.y, 2));
}

int Utility::random(int min, int max)
{
	if (min >= 0 && max > min)
	{
		return (rand() % (max-min+1)) + min;
	}
	else if (min == max)
	{
		return min;
	}
	else if (min < 0 && max > min)
	{
		return (rand() % (abs(min)+max + 1)) + min;
	}

	else if (min > max )
	{
		if (max >= 0)
		{
			return (rand() % (min - max + 1) + max);
		}
		else
		{
			return (rand() % (abs(max)+min + 1)) + min;
		}
	}

	return 0;
}

