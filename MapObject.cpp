#include "MapObject.h"


MapObject::MapObject()
{
	name = "aaaaa";
	passable=false;
}

MapObject::MapObject(int x, int y)
{
	shape.setPosition(x, y);
	name = "aaaaa";
	passable = false;
}

MapObject::MapObject(MapObject& copy)
{
	this->name = copy.name;
	this->shape = copy.shape;

}

void MapObject::setPos(sf::Vector2f paikka)
{
	shape.setPosition(paikka);
	
}

sf::Vector2f MapObject::getSize()
{
	return shape.getSize();
}

sf::Vector2f MapObject::getPos()
{
	return shape.getPosition();
}
std::string MapObject::getName()
{
	return name;
}

MapObject::~MapObject()
{
}