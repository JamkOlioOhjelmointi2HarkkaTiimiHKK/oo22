#pragma once
#include "main.h"
#include <string.h>

class MapObject
{
protected:
	sf::RectangleShape shape;
	std::string name;
public:
	MapObject();
	MapObject(MapObject&);	
	void update(sf::Vector2f);
	void draw();
	void setPos(sf::Vector2f);
	sf::Vector2f getSize();
	sf::Vector2f getPos();
	std::string getName();
	bool passable;
	~MapObject();
};

