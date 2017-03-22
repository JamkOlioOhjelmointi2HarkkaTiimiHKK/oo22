#pragma once
#include "MapObject.h"
#include "Utility.h"

class Cloud : public MapObject
{


public:
	Cloud();
	int size;
	float speed;
	~Cloud();
};

