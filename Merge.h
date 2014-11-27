#pragma once
#include "globals.h"
#include <stdio.h>
#include <fstream>
#include "Block.h"
#include "Floor.h"
#include "Controls.h"
#include "Utility.h"

class MapObject;

class Merge
{
private:
	std::vector<MapObject*> mapObjects;
	std::ifstream file;
	std::fstream facts;
	std::ofstream file2;
	std::string line;
	std::string name;
	std::string x;
	std::string y;
	sf::Vector2f position;

	int numberOfPart;
	int numberOfMap;

	sf::View view;
	void save();
	void update(float);
	void draw();

public:
	Merge();
	void loop(float);
	~Merge();
};

