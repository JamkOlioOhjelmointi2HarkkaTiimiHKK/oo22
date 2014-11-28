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

