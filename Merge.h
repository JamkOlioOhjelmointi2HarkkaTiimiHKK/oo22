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
	std::vector<MapObject*> mapObjects; // Kertan osat s�il�t��n t�nne
	std::vector<MapObject*> partObjects; // kartan osan objektit s�il�t��n t�nne
	std::vector<std::vector<MapObject*>>parts; // palat, jotka s�il�v�t noit� partObjects vektoreita
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

