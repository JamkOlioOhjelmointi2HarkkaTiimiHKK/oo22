#include "globals.h"
#include <stdio.h>
#include <fstream>
#include "Block.h"
#include "Floor.h"
#pragma once
class Map
{
private:

	std::ifstream file;
	std::fstream facts;

	std::string name,line;
	std::string x;
	std::string y;

	int numberOfMap;

	sf::View view;


public:
	std::vector<MapObject*> mapObjects;
	Map();
	void update();
	void draw();
	~Map();
};

