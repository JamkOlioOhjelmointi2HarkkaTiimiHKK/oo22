#pragma once
#include <SFML\Graphics.hpp>
#include "Content.h"
#include <string.h>

class MapObject
{
protected:
	
	std::string name; // tunnistamista varten
	
public:
	sf::RectangleShape shape;
	MapObject();
	MapObject(MapObject&); // editorissa k‰ytet‰‰n
	MapObject(int, int); // mergess‰ ja mapissa k‰ytet‰‰n
	void setPos(sf::Vector2f);
	sf::Vector2f getSize();
	sf::Vector2f getPos();
	std::string getName();
	bool passable;
	~MapObject();
};

