#include "Map.h"


Map::Map()
{
	numberOfMap = 0;

	file.open("Files\\Maps\\MapPart" + std::to_string(numberOfMap) + ".txt");
	while (getline(file, line))
	{
		int temp = line.find(" ");
		name = line.substr(0, temp);
		int temp2 = line.find(" ", temp + 1);
		x = line.substr(temp + 1, temp2 - temp - 1);
		int temp3 = line.find("\n", temp2 + 1);
		y = line.substr(temp2 + 1, temp3 - temp2 - 1);

		if (name.compare("block") == 0)
		{
			mapObjects.push_back(new Block(std::stoi(x), std::stoi(y)));
		}
		else if (name.compare("floor") == 0)
		{
			mapObjects.push_back(new Floor(std::stoi(x), std::stoi(y)));
		}
	}
}

void Map::update()
{

}

void Map::draw()
{
	for (unsigned i = 0; i < mapObjects.size(); ++i)
	{
		window.draw(mapObjects[i]->shape);
	}
}

Map::~Map()
{
}
