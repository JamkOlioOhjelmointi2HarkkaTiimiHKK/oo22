#include "Map.h"


Map::Map()
{
	halfScreenX = SCREEN_WIDTH / 2;
	halfscreenY = SCREEN_HEIGHT / 2;

	numberOfMap = 0;

	file.open("Files\\Maps\\Map" + std::to_string(numberOfMap) + ".txt");
	while (getline(file, line))
	{
		int temp = line.find(" ");
		name = line.substr(0, temp);
		int temp2 = line.find(" ", temp + 1);
		x = line.substr(temp + 1, temp2 - temp - 1);
		int temp3 = line.find("\n", temp2 + 1);
		y = line.substr(temp2 + 1, temp3 - temp2 - 1);

#pragma region vertailu
					if (name.compare("block") == 0)
					{
						mapObjects.push_back(new Block(std::stoi(x), std::stoi(y)));
					}
					else if (name.compare("floor") == 0)
					{
						mapObjects.push_back(new Floor(std::stoi(x) , std::stoi(y)));
					}
					else if (name.compare("ladde") == 0)
					{
						mapObjects.push_back(new Ladder(std::stoi(x), std::stoi(y)));
					}
					else if (name.compare("spawP") == 0)
					{
						mapObjects.push_back(new SpawnPoint(std::stoi(x), std::stoi(y)));
					}
					else if (name.compare("spawE") == 0)
					{
						mapObjects.push_back(new SpawnEnemy(std::stoi(x), std::stoi(y)));
					}
#pragma endregion
	}


}

void Map::update()
{

}

void Map::draw(sf::View view)
{
	for (unsigned i = 0; i < mapObjects.size(); ++i)
	{
		if (mapObjects[i]->getPos().x - view.getCenter().x < halfScreenX && mapObjects[i]->getPos().y - view.getCenter().y < halfscreenY)
		window.draw(mapObjects[i]->shape);
	}
}

Map::~Map()
{
}
