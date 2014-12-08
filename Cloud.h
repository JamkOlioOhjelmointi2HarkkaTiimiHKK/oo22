#pragma once
#include "MapObject.h"
#include <cstdlib>
#include <ctime>
#include "Utility.h"

class Cloud : public MapObject
{


public:
	Cloud();
	float speed;
	~Cloud();
};

