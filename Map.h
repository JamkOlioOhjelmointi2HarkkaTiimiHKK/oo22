#include "globals.h"
#include <stdio.h>
#include <fstream>
#pragma once
class Map
{
private:
	std::ifstream maps;

public:
	Map();
	~Map();
};

