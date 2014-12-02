#include "globals.h"
#include <stdio.h>
#include <fstream>
#include "Block.h"
#include "Floor.h"
#include "Ladder.h"
#include "SpawnPoint.h"
#include "SpawnEnemy.h"
#pragma once
class Map
{
private:

	std::ifstream file;
	std::fstream facts;
	std::string name,line,x,y;

		std::vector<std::vector<MapObject*>> yRivi;
	std::vector<MapObject*> mapObjects;

	int numberOfMap, halfScreenX=0, halfscreenY=0,kerroin;

public:
	std::vector<std::vector<std::vector<MapObject*>>> xRivi;

	Map();
	void update();
	void draw(sf::View);
	~Map();
};

