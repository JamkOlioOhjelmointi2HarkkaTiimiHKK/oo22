#pragma once
#include "globals.h"
#include <stdio.h>
#include <fstream>
#include "Block.h"
#include "Floor.h"

class MapObject;

class Merge
{
private:
	std::vector<MapObject*> mapObjects;
	std::ifstream file;
	std::fstream facts;
	std::string line;
	std::string name;
	std::string x;
	std::string y;
	int numberOfPart;

	void update();
	void draw();

public:
	Merge();
	void loop();
	~Merge();
};

