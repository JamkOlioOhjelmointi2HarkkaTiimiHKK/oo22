#pragma once
#include <stdlib.h>
#include <SFML\Graphics.hpp>
#include <sstream>

namespace Utility
{
	sf::Vector2f makeDirVector(sf::Vector2f &vec);
	sf::Vector2f makeDirVector(sf::Vector2f &from, sf::Vector2f &to);
	bool boxHit(const sf::IntRect &box1, const sf::IntRect &box2);
	bool circleHit(const float rad1, const float rad2, const float dist);
	float distance(const sf::Vector2f &pos1, const sf::Vector2f &pos2);
	float pointToDeg(const sf::Vector2f &to);
	float pointToRad(const sf::Vector2f &to);
	int random(int min, int max);

	template <typename T> std::string tostr(const T& t) { std::ostringstream os; os<<t; return os.str(); }
}