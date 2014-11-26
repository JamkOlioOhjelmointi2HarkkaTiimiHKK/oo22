#pragma once
#include "globals.h"
#include <stdio.h>
#include <fstream>
#include "Block.h"
#include "Floor.h"
#include "Controls.h"

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
	sf::Vector2f position;
	int numberOfPart;

	sf::View view;
	
	void update();
	void draw();

public:
	Merge();
	void loop();
	~Merge();
};

