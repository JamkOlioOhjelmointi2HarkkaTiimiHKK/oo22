#include "globals.h"
#include <stdio.h>
#include <fstream>
#include "Block.h"
#include "Floor.h"
#include "Ladder.h"
#include "SpawnPoint.h"
#include "SpawnEnemy.h"
#include "Merge.h"
#include "Content.h"
#include "Cloud.h"
#pragma once

class Map
{
private:

	sf::RectangleShape tausta1;
	std::ifstream file;
	std::fstream facts;
	std::string name,line,x,y;

	std::vector<std::vector<MapObject*>> yRivi;
	std::vector<MapObject*> mapObjects;

	std::vector<Cloud*> clouds;

	int numberOfMap,kerroin,size;

public:
	std::vector<std::vector<std::vector<MapObject*>>> xRivi;

	Map();
	void update(sf::View, float dt);
	void draw(sf::View);
	int getSize();
	~Map();
};

