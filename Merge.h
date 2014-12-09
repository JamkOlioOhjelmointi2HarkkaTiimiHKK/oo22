#pragma once
#include "globals.h"
#include <stdio.h>
#include <fstream>
#include "Block.h"
#include "Floor.h"
#include "Ladder.h"
#include "SpawnPoint.h"
#include "SpawnEnemy.h"
#include "Controls.h"
#include "Utility.h"

class Merge
{
private:
	std::vector<MapObject*> mapObjects; // Kertan osat säilötään tänne
	std::vector<MapObject*> partObjects; // kartan osan objektit säilötään tänne
	std::vector<std::vector<MapObject*>>parts; // palat, jotka säilövät noitä partObjects vektoreita
	std::ifstream file;
	std::fstream facts;
	std::ofstream file2;
	std::string line,name,x,y,howManyMaps,howManuMapParts;
	sf::Vector2f position;

	int numberOfPart, numberOfMap, halfScreenX, halfscreenY,kerroinY,size;

	sf::View view;
	void Build();
	void save();
	void update(float);
	void draw();
	void killAll();

public:
	Merge();
	void loop(float);
	~Merge();
};

