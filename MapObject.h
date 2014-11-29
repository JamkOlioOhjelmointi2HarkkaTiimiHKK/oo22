#pragma once
#include <SFML\Graphics.hpp>
#include <string.h>

class MapObject
{
protected:
	
	std::string name;
	
public:
	sf::RectangleShape shape;
	MapObject();
	MapObject(MapObject&);
	MapObject(int, int);
	void setPos(sf::Vector2f);
	sf::Vector2f getSize();
	sf::Vector2f getPos();
	std::string getName();
	bool passable;
	~MapObject();
};

