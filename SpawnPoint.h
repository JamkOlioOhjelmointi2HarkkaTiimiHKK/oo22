#pragma once
#include "MapObject.h"

class SpawnPoint : public MapObject
{
protected:
public:
	SpawnPoint();
	SpawnPoint(int, int);
	~SpawnPoint();
};

