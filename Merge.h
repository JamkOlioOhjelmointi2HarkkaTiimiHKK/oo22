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
#include "Button.h"

//class MapObject; mitä vitun mustaa magiaa tämä on

class Merge
{
private:
	std::vector<Button*> buttons;
	std::vector<MapObject*> mapObjects;
	std::vector<MapObject*> partObjects;
	std::vector<std::vector<MapObject*>>parts;
	std::ifstream file;
	std::fstream facts;
	std::ofstream file2;
	std::string line,name,x,y,howManyMaps,howManuMapParts;
	sf::Vector2f position;

	int numberOfPart, numberOfMap, halfScreenX, halfscreenY;

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

